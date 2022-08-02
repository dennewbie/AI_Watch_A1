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

void KafkaManager::load_config_group(rd_kafka_conf_t * conf, GKeyFile * key_file, const char * group) {
    char errstr[512];
    g_autoptr(GError) error = NULL;
    
    gchar ** ptr = g_key_file_get_keys(key_file, group, NULL, &error);
    if (error) {
        g_error("%s", error->message);
        exit(1);
    }
    
    while (*ptr) {
        const char * key = * ptr;
        g_autofree gchar *value = g_key_file_get_string(key_file, group, key, &error);
        if (error) {
            g_error("Reading key: %s", error->message);
            exit(1);
        }
        
        if (rd_kafka_conf_set(conf, key, value, errstr, sizeof(errstr)) != RD_KAFKA_CONF_OK) {
            g_error("%s", errstr);
            exit(1);
        }
        
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



KafkaManager::~KafkaManager (void) {
    setConfiguration(NULL);
    rd_kafka_destroy(getProducer());
}

void KafkaManager::sendData(void) {
    char errorString[512];
    const char * configurationFile = "../configuration_file.ini";
    
    g_autoptr(GError) error = NULL;
    g_autoptr(GKeyFile) key_file = g_key_file_new();
    if (!g_key_file_load_from_file (key_file, configurationFile, G_KEY_FILE_NONE, &error)) {
        g_error ("Error loading config file: %s", error->message);
    }
    
    // Load the relevant configuration sections.
    setConfiguration(rd_kafka_conf_new());
    load_config_group(getConfiguration(), key_file, "default");
    
    // Install a delivery-error callback.
    rd_kafka_conf_set_dr_msg_cb(getConfiguration(), dr_msg_cb);
    
    // Create the Producer instance.
    setProducer(rd_kafka_new(RD_KAFKA_PRODUCER, getConfiguration(), errorString, sizeof(errorString)));
    if (!getProducer()) g_error("Failed to create new producer: %s", errorString);
    
    // Configuration object is now owned, and freed, by the rd_kafka_t instance.
    setConfiguration(NULL);
    
    // Produce data by selecting random values from these lists.
    int message_count = 10;
    const char * topic = "purchases";
    const char * user_ids[6] = {"eabara", "jsmith", "sgarcia", "jbernard", "htanaka", "awalther"};
    const char * products[5] = {"book", "alarm clock", "t-shirts", "gift card", "batteries"};
    
    for (int i = 0; i < message_count; i++) {
        const char * key =  user_ids[arc4random() % getArraySize(user_ids)];
        const char * value =  products[arc4random() % getArraySize(products)];
        size_t key_len = strlen(key);
        size_t value_len = strlen(value);
        
        rd_kafka_resp_err_t err;
        err = rd_kafka_producev(producer,
                                RD_KAFKA_V_TOPIC(getTopic()),
                                RD_KAFKA_V_MSGFLAGS(RD_KAFKA_MSG_F_COPY),
                                RD_KAFKA_V_KEY((void *) key, key_len),
                                RD_KAFKA_V_VALUE((void *)value, value_len),
                                RD_KAFKA_V_OPAQUE(NULL),
                                RD_KAFKA_V_END);
        
        if (err) {
            g_error("Failed to produce to topic %s: %s", topic, rd_kafka_err2str(err));
        } else {
            g_message("Produced event to topic %s: key = %12s value = %12s", topic, key, value);
        }
        
        rd_kafka_poll(producer, 0);
    }
    
    // Block until the messages are all sent.
    g_message("Flushing final messages..");
    rd_kafka_flush(producer, 10 * 1000);
    
    if (rd_kafka_outq_len(producer) > 0) {
        g_error("%d message(s) were not delivered", rd_kafka_outq_len(producer));
    }
    
    g_message("%d events were produced to topic %s.", message_count, topic);
}
