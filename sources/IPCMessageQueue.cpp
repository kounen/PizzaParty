/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** IPCMessageQueue
*/

#include "IPCMessageQueue.hpp"

IPCMessageQueue::IPCMessageQueue()
    : _queuesNumber{0}
{
}

IPCMessageQueue::~IPCMessageQueue()
{
    // Close client message queues
    for (const std::pair<int, mqd_t> &messageQueue : _kitchensClient)
    {
        mq_close(messageQueue.second);
    }
    // Close server message queues
    for (const std::pair<int, mqd_t> &messageQueue : _kitchensServer)
    {
        mq_close(messageQueue.second);
    }
    // Remove client message queues
    for (const std::pair<int, mqd_t> &messageQueue : _kitchensClient)
    {
        mq_unlink(std::string(CLIENT_QUEUE_NAME + std::to_string(messageQueue.first)).c_str());
    }
    // Remove server message queues
    for (const std::pair<int, mqd_t> &messageQueue : _kitchensServer)
    {
        mq_unlink(std::string(SERVER_QUEUE_NAME + std::to_string(messageQueue.first)).c_str());
    }
}

void IPCMessageQueue::createAKitchenMessageQueue(const int &kitchenID)
{
    mqd_t messageQueueDescriptor;

    struct mq_attr attr;
    // Initialize mq_attr structure
    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    // Create client message queue and insert it into respective container (number + 1 because NULL string otherwise)
    std::string clientQueueName(CLIENT_QUEUE_NAME + std::to_string(_queuesNumber + 1));
    if ((messageQueueDescriptor = mq_open(clientQueueName.c_str(), O_RDWR | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1)
    {
        throw std::runtime_error("Error: mq_open (client)");
    }
    std::pair<int, mqd_t> kitchenClient = std::make_pair(kitchenID, messageQueueDescriptor);
    _kitchensClient.push_back(kitchenClient);

    // Create server message queue and insert it into respective container (number + 1 because NULL string otherwise)
    std::string serverQueueName(SERVER_QUEUE_NAME + std::to_string(_queuesNumber + 1));
    if ((messageQueueDescriptor = mq_open(serverQueueName.c_str(), O_RDWR | O_CREAT | O_NONBLOCK, QUEUE_PERMISSIONS, &attr)) == -1)
    {
        throw std::runtime_error("Error: mq_open (server)");
    }
    std::pair<int, mqd_t> kitchenServer = std::make_pair(kitchenID, messageQueueDescriptor);
    _kitchensServer.push_back(kitchenServer);

    _queuesNumber += 1;
}

void IPCMessageQueue::sendMessageFromReceptionToKitchen(const std::string &message, const int &kitchenID) const
{
    int kitchenMessageQueueID = getKitchenMessageQueueID(kitchenID, CLIENT);

    if (mq_send(_kitchensClient[kitchenMessageQueueID].second, message.c_str(), message.length() + 1, MSG_PRIO) == -1)
    {
        throw std::runtime_error("Error: mq_send");
    }
}

void IPCMessageQueue::sendMessageFromKitchenToReception(const std::string &message, mqd_t receptionMessageQueueDescriptor)
{
    if (mq_send(receptionMessageQueueDescriptor, message.c_str(), message.length() + 1, MSG_PRIO) == -1)
    {
        throw std::runtime_error("Error: mq_send");
    }
}

int IPCMessageQueue::receiveMessageFromKitchenInReception(const int &kitchenID, std::string &receiveMessage) const
{
    int kitchenMessageQueueID = getKitchenMessageQueueID(kitchenID, SERVER);
    char msg_ptr[MSG_BUFFER_SIZE] = {0};
    int receiveStatus = mq_receive(_kitchensServer[kitchenMessageQueueID].second, msg_ptr, MSG_BUFFER_SIZE, MSG_PRIO);

    if (receiveStatus == -1 && errno != EAGAIN)
    {
        throw std::out_of_range("Error: mq_receive");
    }
    else if (receiveStatus > 0)
    {
        receiveMessage.assign(msg_ptr);
    }
    return receiveStatus;
}

int IPCMessageQueue::receiveMessageFromReceptionInKitchen(mqd_t receptionMessageQueueDescriptor, std::string &receiveMessage)
{
    char msg_ptr[MSG_BUFFER_SIZE] = {0};
    int receiveStatus = mq_receive(receptionMessageQueueDescriptor, msg_ptr, MSG_BUFFER_SIZE, MSG_PRIO);

    if (receiveStatus == -1)
    {
        throw std::out_of_range("Error: mq_receive");
    }
    else if (receiveStatus > 0)
    {
        receiveMessage.assign(msg_ptr);
    }
    return receiveStatus;
}

int IPCMessageQueue::getKitchenMessageQueueID(const int &kitchenID, const QueueType &queueType) const
{
    int messageQueueID = 0;

    if (queueType == CLIENT)
    {
        for (const std::pair<int, mqd_t> &messageQueue : _kitchensClient)
        {
            if (messageQueue.first == kitchenID)
            {
                break;
            }
            messageQueueID++;
        }
    }
    else if (queueType == SERVER)
    {
        for (const std::pair<int, mqd_t> &messageQueue : _kitchensServer)
        {
            if (messageQueue.first == kitchenID)
            {
                break;
            }
            messageQueueID++;
        }
    }
    return messageQueueID;
}
