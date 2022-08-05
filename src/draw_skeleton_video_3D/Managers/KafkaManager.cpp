//
//  KafkaManager.cpp
//  librealsensetest
//
//  Created by Denny Caruso on 27/07/22.
//

#include "KafkaManager.hpp"



void KafkaManager::setProducer (rd_kafka_t * producer) {
    this->producer = producer;
}

void KafkaManager::setConfiguration (rd_kafka_conf_t * configuration) {
    this->configuration = configuration;
}

rd_kafka_t * KafkaManager::getProducer (void) {
    return this->producer;
}

rd_kafka_conf_t * KafkaManager::getConfiguration (void) {
    return this->configuration;
}

const char * KafkaManager::getTopic (void) {
    return this->topic;
}

void KafkaManager::loadConfigurationGroup(rd_kafka_conf_t * conf, GKeyFile * key_file, const char * group) {
    char errstr[512];
    g_autoptr(GError) error = NULL;
    
    gchar ** ptr = g_key_file_get_keys(key_file, group, NULL, & error);
    if (error) CV_Error(RDKAFKA_GET_KEYS_FROM_JSON_ERROR, RDKAFKA_GET_KEYS_FROM_JSON_SCOPE);
    
    while (* ptr) {
        const char * key = * ptr;
        g_autofree gchar * value = g_key_file_get_string(key_file, group, key, & error);
        if (error) CV_Error(RDKAFKA_GET_KEY_FROM_JSON_ERROR, RDKAFKA_GET_KEY_FROM_JSON_SCOPE);
        
        if (rd_kafka_conf_set(conf, key, value, errstr, sizeof(errstr)) != RD_KAFKA_CONF_OK) CV_Error(RDKAFKA_CONF_SET_ERROR, RDKAFKA_CONF_SET_SCOPE);
        ptr++;
    }
}

int KafkaManager::getArraySize (const char ** array) {
    return (sizeof(array) / sizeof(array[0]));
}

/**
 * @brief Optional per-message delivery callback (triggered by poll() or flush())
 * when a message has been successfully delivered or permanently
 * failed delivery (after retries).
 */
void KafkaManager::dr_msg_cb (rd_kafka_t * kafka_handle, const rd_kafka_message_t * rkmessage, void * opaque) {
    if (rkmessage->err) g_error("Message delivery failed: %s", rd_kafka_err2str(rkmessage->err));
}

void KafkaManager::setupProducer (void) {
    char errorString[512];
    const char * configurationFile = "../configuration_file.ini";
    
    g_autoptr(GError) error = NULL;
    g_autoptr(GKeyFile) key_file = g_key_file_new();
    if (!g_key_file_load_from_file (key_file, configurationFile, G_KEY_FILE_NONE, & error)) {
        g_error ("Error loading config file: %s", error->message);
    }
    
    // Load the relevant configuration sections.
    setConfiguration(rd_kafka_conf_new());
    loadConfigurationGroup(getConfiguration(), key_file, "default");
    
    // Install a delivery-error callback.
    rd_kafka_conf_set_dr_msg_cb(getConfiguration(), dr_msg_cb);
    
    // Create the Producer instance.
    setProducer(rd_kafka_new(RD_KAFKA_PRODUCER, getConfiguration(), errorString, sizeof(errorString)));
    if (!getProducer()) g_error("Failed to create new producer: %s", errorString);
    
    // Configuration object is now owned, and freed, by the rd_kafka_t instance.
    setConfiguration(NULL);
}



KafkaManager::~KafkaManager (void) {
    setConfiguration(NULL);
    rd_kafka_destroy(getProducer());
}

void KafkaManager::sendData (const char * key, Json::Value root) {
    // Produce data
//    int message_count = 10;
    std::string keyString = root.toStyledString();
    const char * value = keyString.c_str();
    size_t messageSize = (size_t) keyString.size();
    rd_kafka_resp_err_t err = rd_kafka_producev(getProducer(),
                                                RD_KAFKA_V_TOPIC(getTopic()),
                                                RD_KAFKA_V_MSGFLAGS(RD_KAFKA_MSG_F_COPY),
                                                RD_KAFKA_V_KEY((void *) key, strlen(key) * sizeof(char)),
                                                RD_KAFKA_V_VALUE((void *) value, messageSize),
                                                RD_KAFKA_V_OPAQUE(NULL), RD_KAFKA_V_END);
                      
    if (err) g_error("Failed to produce to topic %s: %s", topic, rd_kafka_err2str(err));
    /* } else {
           g_message("Produced event to topic %s: key = %12s value = %12s", topic, key, value);
       }
    */
    
    rd_kafka_poll(producer, 0);
    // Block until the messages are all sent.
    // g_message("Flushing final messages..");
    rd_kafka_flush(producer, 10 * 1000);
    
    if (rd_kafka_outq_len(producer) > 0) g_error("%d message(s) were not delivered", rd_kafka_outq_len(producer));
//    g_message("%d events were produced to topic %s.", message_count, topic);
}
