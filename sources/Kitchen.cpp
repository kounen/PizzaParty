/*
** EPITECH PROJECT, 2021
** B-CCP-400-LYN-4-1-theplazza-lucas.guichard
** File description:
** Kitchen
*/

#include "Kitchen.hpp"

Kitchen::Kitchen(const int &kitchenID, const float &cookingTime, const int &cooksNumber, const int &stockTime)
    : _kitchenID{kitchenID}, _cookingTime{cookingTime}, _cooksNumber{cooksNumber}, _stockTime{stockTime}
{
    try
    {
        createMessageQueue();
    }
    catch(const std::runtime_error &error)
    {
        std::cerr << error.what() << std::endl;
    }
    createThreadPool();
}

Kitchen::~Kitchen()
{
    // Close client message queue
    mq_close(_messageQueueDescriptor.first);
    // Close server message queue
    mq_close(_messageQueueDescriptor.second);
    // Remove client message queue
    mq_unlink(std::string(CLIENT_QUEUE_NAME + std::to_string(_kitchenID)).c_str());
    // Remove server message queue
    mq_unlink(std::string(SERVER_QUEUE_NAME + std::to_string(_kitchenID)).c_str());
}

void Kitchen::createMessageQueue()
{
    mqd_t messageQueueDescriptorClient, messageQueueDescriptorServer;

    struct mq_attr attr;
    // Initialize mq_attr structure
    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    // Create client message queue
    std::string clientQueueName(CLIENT_QUEUE_NAME + std::to_string(_kitchenID));
    if ((messageQueueDescriptorClient = mq_open(clientQueueName.c_str(), O_RDWR | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1)
    {
        throw std::runtime_error("Error: mq_open (client)");
    }

    // Create server message queue
    std::string serverQueueName(SERVER_QUEUE_NAME + std::to_string(_kitchenID));
    if ((messageQueueDescriptorServer = mq_open(serverQueueName.c_str(), O_RDWR | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1)
    {
        throw std::runtime_error("Error: mq_open (server)");
    }

    // Paired the two message queues
    _messageQueueDescriptor = std::make_pair(messageQueueDescriptorClient, messageQueueDescriptorServer);
}

void Kitchen::createThreadPool()
{
    for (int i = 0; i < _cooksNumber; i++)
    {
        _threadPool.push_back(Cook::hireACook(_messageQueueDescriptor, _cookingTime, _stockTime));
    }
    for (std::thread &thread : _threadPool)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }
}
