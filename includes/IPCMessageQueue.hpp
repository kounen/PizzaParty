/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** IPCMessageQueue
*/

#ifndef IPCMESSAGEQUEUE_HPP_
#define IPCMESSAGEQUEUE_HPP_

#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>

#define CLIENT_QUEUE_NAME "/plazza-client-"
#define SERVER_QUEUE_NAME "/plazza-server-"

#define QUEUE_PERMISSIONS (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256

#define MSG_PRIO 0
#define MSG_BUFFER_SIZE (MAX_MSG_SIZE + 10)

class IPCMessageQueue {
    public:
        IPCMessageQueue();
        ~IPCMessageQueue();
        IPCMessageQueue(const IPCMessageQueue &) = delete;
        IPCMessageQueue(IPCMessageQueue &&) = delete;
        IPCMessageQueue &operator=(IPCMessageQueue &&) = delete;
        IPCMessageQueue &operator=(const IPCMessageQueue &) = delete;

        void createAKitchenMessageQueue(const int &kitchenID);
        void sendMessageFromReceptionToKitchen(const std::string &message, const int &kitchenID) const;
        static void sendMessageFromKitchenToReception(const std::string &message, mqd_t receptionMessageQueueDescriptor);
        int receiveMessageFromKitchenInReception(const int &kitchenID, std::string &receiveMessage) const;
        static int receiveMessageFromReceptionInKitchen(mqd_t receptionMessageQueueDescriptor, std::string &receiveMessage);

        // Operator overloading for << : write _queuesNumber to stream
        friend std::ostream &operator<<(std::ostream &output, const IPCMessageQueue &IPCSystem) {
            output << "Number of kitchen queues : " << IPCSystem._queuesNumber;
            return output;
        }

        // Operator overloading for >> : set _queuesNumber from stream
        friend std::istream& operator>>(std::istream &input, IPCMessageQueue &IPCSystem) {
            input >> IPCSystem._queuesNumber;
            return input;
        }

    private:
        enum QueueType {
            CLIENT,
            SERVER
        };

        int _queuesNumber;

        // pair<kitchenID, messageQueueDescriptor>, a client and server queue for each kitchen
        std::vector<std::pair<int, mqd_t>> _kitchensClient;
        std::vector<std::pair<int, mqd_t>> _kitchensServer;

        int getKitchenMessageQueueID(const int &kitchenID, const QueueType &queueType) const;
};

#endif /* !IPCMESSAGEQUEUE_HPP_ */
