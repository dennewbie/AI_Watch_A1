//
//  KafkaManager.hpp
//  librealsensetest
//
//  Created by Denny Caruso on 27/07/22.
//

#ifndef KafkaManager_hpp
#define KafkaManager_hpp

#include <librdkafka/rdkafka.h>
#include <glib.h>
#include <json/value.h>
#include <opencv2/core.hpp>
#include "../constants.hpp"



class KafkaManager {
private:
    rd_kafka_t *        producer;
    rd_kafka_conf_t *   configuration;
    const char *        topic;
    
    void setProducer        (rd_kafka_t * producer);
    void setConfiguration   (rd_kafka_conf_t * configuration);
    
    rd_kafka_t * getProducer              (void);
    rd_kafka_conf_t * getConfiguration    (void);
    const char * getTopic                 (void);
    
    void loadConfigurationGroup     (rd_kafka_conf_t * conf, GKeyFile * key_file, const char * group);
    int getArraySize                (const char ** array);
    static void dr_msg_cb           (rd_kafka_t * kafka_handle, const rd_kafka_message_t * rkmessage, void * opaque);
    void setupProducer      (void);
public:
    KafkaManager            (const char * topic) : topic(topic) {
        setupProducer();
    }
    ~KafkaManager           (void);
    void sendData           (const char * key, Json::Value root);
};


#endif /* KafkaManager_hpp */
