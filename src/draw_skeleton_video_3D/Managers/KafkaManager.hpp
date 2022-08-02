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
#include <iostream>



class KafkaManager {
private:
    rd_kafka_t *        producer;
    rd_kafka_conf_t *   configuration;
    const char *        topic;
    
    void setProducer        (rd_kafka_t * producer);
    void setConfiguration   (rd_kafka_conf_t * configuration);
    
    rd_kafka_t * getProducer              (void);
    rd_kafka_conf_t * getConfiguration    (void);
    const char * getTopic                       (void);
    
    void load_config_group  (rd_kafka_conf_t * conf, GKeyFile * key_file, const char * group);
    int getArraySize        (const char ** array);
    static void dr_msg_cb          (rd_kafka_t * kafka_handle, const rd_kafka_message_t * rkmessage, void * opaque);
public:
    KafkaManager            (const char * topic) : topic(topic) { }
    ~KafkaManager           (void);
    void sendData           (void);
};


#endif /* KafkaManager_hpp */
