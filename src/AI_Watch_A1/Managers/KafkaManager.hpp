//
//  KafkaManager.hpp
//  AI Watch A1
//
//  Created by Denny Caruso on 27/07/22.
//

// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022. All Rights Reserved.

#ifndef KafkaManager_hpp
#define KafkaManager_hpp

#include <librdkafka/rdkafka.h>
#include <glib.h>
#include <json/value.h>
#include <opencv2/core.hpp>
#include "../constants.hpp"



/**
 * Skeleton class is a class that keeps track of the image different frames where a specific skeleton may appears, 
 * its body key points, correspondent 3D space points, and other useful information skeleton-related.
 * @brief Skeleton class is used for skeleton creations and manipulations.
 */
class KafkaManager {
private:
    /**
     * @brief Kafka producer's instance.
     */
    rd_kafka_t *        producer;
    /**
     * @brief Kafka's configuration.
     */
    rd_kafka_conf_t *   configuration;
    /**
     * @brief Destination Kafka's topic.
     */
    const char *        topic;
    


    /**
     * @brief Set the Kafka producer's instance.
     * @param producer Kafka producer's instance.
     */
    void setProducer        (rd_kafka_t * producer);
    /**
     * @brief Set the Kafka's configuration.
     * @param configuration Kafka's configuration.
     */
    void setConfiguration   (rd_kafka_conf_t * configuration);
    


    /**
     * @brief Get the Kafka producer's instance.
     * @return rd_kafka_t * 
     */
    rd_kafka_t * getProducer              (void);
    /**
     * @brief Get the Kafka's configuration.
     * @return rd_kafka_conf_t * 
     */
    rd_kafka_conf_t * getConfiguration    (void);
    /**
     * @brief Get the destination Kafka's topic.
     * @return const char * 
     */
    const char * getTopic                 (void);
    


    /**
     * @brief Loads the configuration from Kafka's configuration file.
     * @param conf 
     * @param key_file 
     * @param group 
     */
    void loadConfigurationGroup     (rd_kafka_conf_t * conf, GKeyFile * key_file, const char * group);
    /**
     * @brief Get the "const char *" array size.
     * @param array 
     * @return int 
     * @see https://github.com/edenhill/librdkafka/blob/master/CONFIGURATION.md
     */
    int getArraySize                (const char ** array);
    /**
     * @brief Optional per-message delivery callback (triggered by poll() or flush())
     * when a message has been successfully delivered or permanently
     * failed delivery (after retries).
     * @param kafka_handle 
     * @param rkmessage 
     * @param opaque 
    */
    static void dr_msg_cb           (rd_kafka_t * kafka_handle, const rd_kafka_message_t * rkmessage, void * opaque);
    /**
     * @brief Launches configuration loading once reads all the configuration parameters and 
     * later set the producer instance.
     */
    void setupProducer              (void);
public:
    /**
     * @brief Construct a new Kafka Manager object.
     * @param topic Destination Kafka's topic.
     */
    KafkaManager            (const char * topic) : topic(topic) {
        setupProducer();
    }
    /**
     * @brief Destroy the KafkaManager object.
     */
    ~KafkaManager           (void);
    /**
     * @brief Send data contained in root via Kafka with ID equal to key.
     * @param key 
     * @param root 
     */
    void sendData           (const char * key, Json::Value root);
};


#endif /* KafkaManager_hpp */
