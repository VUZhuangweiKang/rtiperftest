/*
 * (c) 2005-2018  Copyright, Real-Time Innovations, Inc. All rights reserved.
 * Subject to Eclipse Public License v1.0; see LICENSE.md for details.
 */

#include "ParameterManager.h"
#include "perftest_cpp.h"

ParameterManager::ParameterManager() {}

ParameterManager& ParameterManager::GetInstance()
{
    static ParameterManager instance;
    return instance;
}

void ParameterManager::initialize()
{
    // GENERAL PARAMETER
    Parameter<bool> *bestEffort = new Parameter<bool>(false);
    bestEffort->set_command_line_argument("-bestEffort","");
    bestEffort->set_description("Run test in best effort mode. Default: reliable");
    bestEffort->set_type(T_BOOL);
    bestEffort->set_extra_argument(NO);
    bestEffort->set_group(GENERAL);
    _parameterList["bestEffort"] = AnyParameter(bestEffort);

    Parameter<unsigned long long> *dataLen = new Parameter<unsigned long long>(100);
    dataLen->set_command_line_argument("-dataLen","<bytes>");
    dataLen->set_description("Set length of payload for each send.\nDefault: 100");
    dataLen->set_type(T_NUMERIC_LLU);
    dataLen->set_extra_argument(YES);
    dataLen->set_range(perftest_cpp::OVERHEAD_BYTES, MAX_PERFTEST_SAMPLE_SIZE);
    dataLen->set_group(GENERAL);
    _parameterList["dataLen"] = AnyParameter(dataLen);

    Parameter<int> *verbosity = new Parameter<int>(1);
    verbosity->set_command_line_argument("-verbosity","<level>");
    verbosity->set_description("Run with different levels of verbosity:\n0 - SILENT, 1 - ERROR, 2 - WARNING, 3 - ALL.\nDefault: 1");
    verbosity->set_type(T_NUMERIC_D);
    verbosity->set_extra_argument(YES);
    verbosity->set_range(0, 3);
    verbosity->set_group(GENERAL);
    _parameterList["verbosity"] = AnyParameter(verbosity);

    Parameter<bool> *dynamicData = new Parameter<bool>(false);
    dynamicData->set_command_line_argument("-dynamicData","");
    dynamicData->set_description("Makes use of the Dynamic Data APIs instead\nof using the generated types");
    dynamicData->set_type(T_BOOL);
    dynamicData->set_extra_argument(NO);
    dynamicData->set_group(GENERAL);
    _parameterList["dynamicData"] = AnyParameter(dynamicData);

    Parameter<int> *durability = new Parameter<int>(DDS_VOLATILE_DURABILITY_QOS);
    durability->set_command_line_argument("-durability","<0|1|2|3>");
    durability->set_description("Set durability QOS: 0 - volatile,\n1 - transient local, 2 - transient,\n3 - persistent. Default: 0");
    durability->set_type(T_NUMERIC_D);
    durability->set_extra_argument(YES);
    durability->set_group(GENERAL);
    durability->set_range(0, 3);
    _parameterList["durability"] = AnyParameter(durability);

    Parameter<int> *domain = new Parameter<int>(1);
    domain->set_command_line_argument("-domain","<id>");
    domain->set_description("RTI DDS Domain. Default: 1");
    domain->set_type(T_NUMERIC_D);
    domain->set_extra_argument(YES);
    domain->set_range(0, 250);
    domain->set_group(GENERAL);
    _parameterList["domain"] = AnyParameter(domain);

    Parameter<unsigned long long> *instances = new Parameter<unsigned long long>(1);
    instances->set_command_line_argument("-instances","<count>");
    instances->set_description("Set the number of instances (keys) to iterate\nover when publishing. Default: 1");
    instances->set_type(T_NUMERIC_LLU);
    instances->set_extra_argument(YES);
    instances->set_range(1, ULONG_MAX);
    instances->set_group(GENERAL);
    _parameterList["instances"] = AnyParameter(instances);

    Parameter<unsigned long long> *instanceHashBuckets = new Parameter<unsigned long long>(0);
    instanceHashBuckets->set_command_line_argument("-instanceHashBuckets","<count>");
    instanceHashBuckets->set_internal(true);
    instanceHashBuckets->set_type(T_NUMERIC_LLU);
    instanceHashBuckets->set_extra_argument(YES);
    instanceHashBuckets->set_range(1, 1000000);
    instanceHashBuckets->set_group(GENERAL);
    _parameterList["instanceHashBuckets"] = AnyParameter(instanceHashBuckets);

    Parameter<bool> *keyed = new Parameter<bool>(false);
    keyed->set_command_line_argument("-keyed","");
    keyed->set_description("Use keyed data. Default: unkeyed");
    keyed->set_type(T_BOOL);
    keyed->set_extra_argument(NO);
    keyed->set_group(GENERAL);
    _parameterList["keyed"] = AnyParameter(keyed);

    Parameter<bool> *noDirectCommunication = new Parameter<bool>(false);
    noDirectCommunication->set_command_line_argument("-noDirectCommunication","");
    noDirectCommunication->set_description("Use brokered mode for persistent durability");
    noDirectCommunication->set_type(T_BOOL);
    noDirectCommunication->set_extra_argument(NO);
    noDirectCommunication->set_group(GENERAL);
    _parameterList["noDirectCommunication"] = AnyParameter(noDirectCommunication);

    Parameter<bool> *noPositiveAcks = new Parameter<bool>(false);
    noPositiveAcks->set_command_line_argument("-noPositiveAcks","");
    noPositiveAcks->set_description("Disable use of positive acks in reliable \nprotocol. Default use positive acks");
    noPositiveAcks->set_type(T_BOOL);
    noPositiveAcks->set_extra_argument(NO);
    noPositiveAcks->set_group(GENERAL);
    _parameterList["noPositiveAcks"] = AnyParameter(noPositiveAcks);

    Parameter<unsigned long long> *keepDurationUsec = new Parameter<unsigned long long>(0);
    keepDurationUsec->set_command_line_argument("-keepDurationUsec","<usec>");
    keepDurationUsec->set_internal(true);
    keepDurationUsec->set_type(T_NUMERIC_LLU);
    keepDurationUsec->set_extra_argument(YES);
    keepDurationUsec->set_group(GENERAL);
    keepDurationUsec->set_range(1, ULLONG_MAX);
    _parameterList["keepDurationUsec"] = AnyParameter(keepDurationUsec);

    Parameter<bool> *noPrintIntervals = new Parameter<bool>(false);
    noPrintIntervals->set_command_line_argument("-noPrintIntervals","");
    noPrintIntervals->set_description("Don't print statistics at intervals during\ntest");
    noPrintIntervals->set_type(T_BOOL);
    noPrintIntervals->set_extra_argument(NO);
    noPrintIntervals->set_group(GENERAL);
    _parameterList["noPrintIntervals"] = AnyParameter(noPrintIntervals);

    Parameter<std::string> *qosFile = new Parameter<std::string>("perftest_qos_profiles.xml");
    qosFile->set_command_line_argument("-qosFile","<filename>");
    qosFile->set_description("Name of XML file for DDS Qos profiles.\nDefault: perftest_qos_profiles.xml");
    qosFile->set_type(T_STR);
    qosFile->set_extra_argument(YES);
    qosFile->set_group(GENERAL);
    _parameterList["qosFile"] = AnyParameter(qosFile);

    Parameter<std::string> *qosLibrary = new Parameter<std::string>("PerftestQosLibrary");
    qosLibrary->set_command_line_argument("-qosLibrary","<lib name>");
    qosLibrary->set_description("Name of QoS Library for DDS Qos profiles.\nDefault: PerftestQosLibrary");
    qosLibrary->set_type(T_STR);
    qosLibrary->set_extra_argument(YES);
    qosLibrary->set_group(GENERAL);
    _parameterList["qosLibrary"] = AnyParameter(qosLibrary);

    Parameter<bool> *noXmlQos = new Parameter<bool>(false);
    noXmlQos->set_command_line_argument("-noXmlQos","");
    noXmlQos->set_description("Skip loading the qos profiles from the xml\nprofile");
    noXmlQos->set_type(T_BOOL);
    noXmlQos->set_extra_argument(NO);
    noXmlQos->set_group(GENERAL);
    _parameterList["noXmlQos"] = AnyParameter(noXmlQos);

    Parameter<bool> *useReadThread = new Parameter<bool>(false);
    useReadThread->set_command_line_argument("-useReadThread","");
    useReadThread->set_description("Use separate thread instead of callback to\nread data");
    useReadThread->set_type(T_BOOL);
    useReadThread->set_extra_argument(NO);
    useReadThread->set_group(GENERAL);
    _parameterList["useReadThread"] = AnyParameter(useReadThread);

    Parameter<unsigned long long> *waitsetDelayUsec = new Parameter<unsigned long long>(100);
    waitsetDelayUsec->set_command_line_argument("-waitsetDelayUsec","<usec>");
    waitsetDelayUsec->set_description("UseReadThread related. Allows you to\nprocess incoming data in groups, based on the\ntime rather than individually. It can be used\ncombined with -waitsetEventCount.\nDefault: 100 usec");
    waitsetDelayUsec->set_type(T_NUMERIC_LLU);
    waitsetDelayUsec->set_extra_argument(YES);
    waitsetDelayUsec->set_group(GENERAL);
    waitsetDelayUsec->set_range(0, UINT_MAX);
    _parameterList["waitsetDelayUsec"] = AnyParameter(waitsetDelayUsec);

    Parameter<unsigned long long> *waitsetEventCount = new Parameter<unsigned long long>(5);
    waitsetEventCount->set_command_line_argument("-waitsetEventCount","<count>");
    waitsetEventCount->set_description("UseReadThread related. Allows you to\nprocess incoming data in groups, based on the\nnumber of samples rather than individually. It\ncan be used combined with -waitsetDelayUsec.\nDefault: 5");
    waitsetEventCount->set_type(T_NUMERIC_LLU);
    waitsetEventCount->set_extra_argument(YES);
    waitsetEventCount->set_group(GENERAL);
    waitsetEventCount->set_range(1, ULLONG_MAX);
    _parameterList["waitsetEventCount"] = AnyParameter(waitsetEventCount);

    Parameter<bool> *asynchronous = new Parameter<bool>(false);
    asynchronous->set_command_line_argument("-asynchronous","");
    asynchronous->set_description("Use asynchronous writer.\nDefault: Not set");
    asynchronous->set_type(T_BOOL);
    asynchronous->set_extra_argument(NO);
    asynchronous->set_group(GENERAL);
    _parameterList["asynchronous"] = AnyParameter(asynchronous);

    Parameter<std::string> *flowController = new Parameter<std::string>("default");
    flowController->set_command_line_argument("-flowController", "<flow>");
    flowController->set_description("In the case asynchronous writer use a specific flow controller.\nThere are several flow controller predefined:\n\t{'default', '1Gbps', '10Gbps'}\nDefault: \"default\" (If using asynchronous)");
    flowController->set_type(T_STR);
    flowController->set_extra_argument(YES);
    flowController->add_valid_str_value("default");
    flowController->add_valid_str_value("1Gbps");
    flowController->add_valid_str_value("10Gbps");
    flowController->set_group(GENERAL);
    _parameterList["flowController"] = AnyParameter(flowController);

    Parameter<bool> *cpu = new Parameter<bool>(false);
    cpu->set_command_line_argument("-cpu","");
    cpu->set_description("Display the cpu percent use by the process\nDefault: Not set");
    cpu->set_type(T_BOOL);
    cpu->set_extra_argument(NO);
    cpu->set_group(GENERAL);
    _parameterList["cpu"] = AnyParameter(cpu);

    Parameter<int> *unbounded = new Parameter<int>(0);
    unbounded->set_command_line_argument("-unbounded","<allocation_threshold>");
    unbounded->set_description("Use unbounded Sequences\n<allocation_threshold> is optional. Default: 63000 Bytes");
    unbounded->set_type(T_NUMERIC_D);
    unbounded->set_extra_argument(OPTIONAL);
    unbounded->set_range(perftest_cpp::OVERHEAD_BYTES, MAX_BOUNDED_SEQ_SIZE);
    unbounded->set_group(GENERAL);
    _parameterList["unbounded"] = AnyParameter(unbounded);

    Parameter<std::string> *threadPriorities = new Parameter<std::string>("");
    threadPriorities->set_command_line_argument("-threadPriorities","<:A:B:C>");
    threadPriorities->set_description("Set the priorities for the Main thread(A), \nReceive threads(B) created by the participant\nand Receive listener threads(B) when -UseReadThread is provide\nand Event and DataBase(C) threads\ncreated by each DomainParticipant\n");
    threadPriorities->set_type(T_STR);
    threadPriorities->set_extra_argument(YES);
    threadPriorities->set_group(GENERAL);
    _parameterList["threadPriorities"] = AnyParameter(threadPriorities);


    ////////////////////////////////////////////////////////////////////////////
    //PUBLISHER PARAMETER

    Parameter<long> *batchSize = new Parameter<long>(DEFAULT_THROUGHPUT_BATCH_SIZE);
    batchSize->set_command_line_argument("-batchsize","<bytes>");
    batchSize->set_description("Size in bytes of batched message. Default: 8kB.\n(Disabled for LatencyTest mode or if dataLen > 4kB)");
    batchSize->set_type(T_NUMERIC_LD);
    batchSize->set_extra_argument(YES);
    batchSize->set_range(0, MAX_SYNCHRONOUS_SIZE - 1);
    batchSize->set_group(PUB);
    _parameterList["batchSize"] = AnyParameter(batchSize);

    Parameter<bool> *enableAutoThrottle = new Parameter<bool>(false);
    enableAutoThrottle->set_command_line_argument("-enableAutoThrottle","");
    enableAutoThrottle->set_description("Enables the AutoThrottling feature in the\nthroughput DataWriter (pub)");
    enableAutoThrottle->set_type(T_BOOL);
    enableAutoThrottle->set_extra_argument(NO);
    enableAutoThrottle->set_group(PUB);
    _parameterList["enableAutoThrottle"] = AnyParameter(enableAutoThrottle);

    Parameter<bool> *enableTurboMode = new Parameter<bool>(false);
    enableTurboMode->set_command_line_argument("-enableTurboMode","");
    enableTurboMode->set_description("Enables the TurboMode feature in the\nthroughput DataWriter (pub)");
    enableTurboMode->set_type(T_BOOL);
    enableTurboMode->set_extra_argument(NO);
    enableTurboMode->set_group(PUB);
    _parameterList["enableTurboMode"] = AnyParameter(enableTurboMode);

    Parameter<bool> * pub = new Parameter<bool>(false);
    pub->set_command_line_argument("-pub","");
    pub->set_description("Set test to be a publisher");
    pub->set_type(T_BOOL);
    pub->set_extra_argument(NO);
    pub->set_group(PUB);
    _parameterList["pub"] = AnyParameter(pub);

    Parameter<unsigned long long> *latencyCount = new Parameter<unsigned long long>(10000);
    latencyCount->set_command_line_argument("-latencyCount","<count>");
    latencyCount->set_description("Number of samples (or batches) to send before\na latency ping packet is sent. Default:\n10000 if -latencyTest is not specified,\n1 if -latencyTest is specified");
    latencyCount->set_type(T_NUMERIC_LLU);
    latencyCount->set_extra_argument(YES);
    latencyCount->set_range(0, ULLONG_MAX);
    latencyCount->set_group(PUB);
    _parameterList["latencyCount"] = AnyParameter(latencyCount);

    Parameter<unsigned long long> *executionTime = new Parameter<unsigned long long>(0);
    executionTime->set_command_line_argument("-executionTime","<sec>");
    executionTime->set_description("Set a maximum duration for the test.\nThe first condition triggered will finish the\ntest: number of samples or execution time.\nDefault 0 (don't set execution time)");
    executionTime->set_type(T_NUMERIC_LLU);
    executionTime->set_extra_argument(YES);
    executionTime->set_range(1, ULLONG_MAX);
    executionTime->set_group(PUB);
    _parameterList["executionTime"] = AnyParameter(executionTime);

    Parameter<bool> *latencyTest = new Parameter<bool>(false);
    latencyTest->set_command_line_argument("-latencyTest","");
    latencyTest->set_description("Run a latency test consisting of a ping-pong\nsynchronous communication");
    latencyTest->set_type(T_BOOL);
    latencyTest->set_extra_argument(NO);
    latencyTest->set_group(PUB);
    _parameterList["latencyTest"] = AnyParameter(latencyTest);

    Parameter<unsigned long long> *numIter = new Parameter<unsigned long long>(100000000);
    numIter->set_command_line_argument("-numIter","<count>");
    numIter->set_description("Set number of messages to send. Default:\n100000000 for Throughput tests or 10000000\nfor Latency tests. See '-executionTime'");
    numIter->set_type(T_NUMERIC_LLU);
    numIter->set_extra_argument(YES);
    numIter->set_range(1, ULLONG_MAX);
    numIter->set_group(PUB);
    _parameterList["numIter"] = AnyParameter(numIter);

    Parameter<int> *numSubscribers = new Parameter<int>(1);
    numSubscribers->set_command_line_argument("-numSubscribers","<count>");
    numSubscribers->set_description("Number of subscribers running in test.\nDefault: 1");
    numSubscribers->set_type(T_NUMERIC_D);
    numSubscribers->set_extra_argument(YES);
    numSubscribers->set_range(1, INT_MAX);
    numSubscribers->set_group(PUB);
    _parameterList["numSubscribers"] = AnyParameter(numSubscribers);

    Parameter<int> *pidMultiPubTest = new Parameter<int>(0);
    pidMultiPubTest->set_command_line_argument("-pidMultiPubTest","<bytes>");
    pidMultiPubTest->set_description("Set id of the publisher in a multi-publisher test.\n Only publisher 0 sends \n latency pings. Default: 0");
    pidMultiPubTest->set_type(T_NUMERIC_D);
    pidMultiPubTest->set_extra_argument(YES);
    pidMultiPubTest->set_range(0, INT_MAX);
    pidMultiPubTest->set_group(PUB);
    _parameterList["pidMultiPubTest"] = AnyParameter(pidMultiPubTest);

    ParameterPair<unsigned long long, std::string> *pubRate = new ParameterPair<unsigned long long, std::string>(0,"spin");
    pubRate->set_command_line_argument("-pubRate","<samples/s>:<method>");
    pubRate->set_description("Limit the throughput to the specified number\nof samples/s. Default 0 (don't limit)\n[OPTIONAL] Method to control the throughput can be:\n'spin' or 'sleep'.\nDefault method: spin");
    pubRate->set_type(T_PAIR_NUMERIC_STR);
    pubRate->set_extra_argument(YES);
    pubRate->set_group(PUB);
    pubRate->set_range(1, 10000000);
    pubRate->add_valid_str_value("sleep");
    pubRate->add_valid_str_value("spin");
    _parameterList["pubRate"] = AnyParameter(pubRate);

     std::vector<unsigned long long> scanList;
    scanList.push_back(32);
    scanList.push_back(64);
    scanList.push_back(128);
    scanList.push_back(256);
    scanList.push_back(512);
    scanList.push_back(1024);
    scanList.push_back(2048);
    scanList.push_back(4096);
    scanList.push_back(8192);
    scanList.push_back(16384);
    scanList.push_back(32768);
    scanList.push_back(63000);
    ParameterVector<unsigned long long> * scan = new ParameterVector<unsigned long long>(scanList);
    scan->set_command_line_argument("-scan","<size1>:<size2>:...:<sizeN>");
    scan->set_description("Run test in scan mode, traversing\na range of sample data sizes from\n[32,63000] or [63001,2147483128] bytes,\nin the case that you are using large data or not.\nThe list of sizes is optional.\nDefault values are '32:64:128:256:512:1024:2048:4096:8192:16384:32768:63000'\nDefault: Not set");
    scan->set_type(T_VECTOR_NUMERIC);
    scan->set_extra_argument(OPTIONAL);
    scan->set_range(perftest_cpp::OVERHEAD_BYTES, MAX_PERFTEST_SAMPLE_SIZE);
    scan->set_parse_method(SPLIT);
    scan->set_group(PUB);
    _parameterList["scan"] = AnyParameter(scan);

    Parameter<int> *sendQueueSize = new Parameter<int>(50);
    sendQueueSize->set_command_line_argument("-sendQueueSize","<number>");
    sendQueueSize->set_description("Sets number of samples (or batches) in send\nqueue. Default: 50");
    sendQueueSize->set_type(T_NUMERIC_D);
    sendQueueSize->set_extra_argument(YES);
    sendQueueSize->set_group(PUB);
    sendQueueSize->set_range(1, INT_MAX);
    _parameterList["sendQueueSize"] = AnyParameter(sendQueueSize);

    Parameter<unsigned long long> *sleep = new Parameter<unsigned long long>(0);
    sleep->set_command_line_argument("-sleep","<millisec>");
    sleep->set_description("Time to sleep between each send. Default: 0");
    sleep->set_type(T_NUMERIC_LLU);
    sleep->set_extra_argument(YES);
    sleep->set_range(0, ULLONG_MAX);
    sleep->set_group(PUB);
    _parameterList["sleep"] = AnyParameter(sleep);

    Parameter<unsigned long long> *spin = new Parameter<unsigned long long>(0);
    spin->set_command_line_argument("-spin","<count>");
    spin->set_internal(true);
    spin->set_type(T_NUMERIC_LLU);
    spin->set_extra_argument(YES);
    spin->set_range(0, ULLONG_MAX);
    spin->set_group(PUB);
    _parameterList["spin"] = AnyParameter(spin);

    Parameter<bool> *writerStats = new Parameter<bool>(false);
    writerStats->set_command_line_argument("-writerStats","");
    writerStats->set_description("Display the Pulled Sample count stats for\nreliable protocol debugging purposes.\nDefault: Not set");
    writerStats->set_type(T_BOOL);
    writerStats->set_extra_argument(NO);
    writerStats->set_group(PUB);
    _parameterList["writerStats"] = AnyParameter(writerStats);

    Parameter<long> *writeInstance = new Parameter<long>(-1);// (-1) By default use round-robin (-1)
    writeInstance->set_command_line_argument("-writeInstance","<instance>");
    writeInstance->set_description("Set the instance number to be sent. \n'-writeInstance' parameter cannot be bigger than the number of instances.\nDefault: 'Round-Robin' schedule");
    writeInstance->set_type(T_NUMERIC_LD);
    writeInstance->set_extra_argument(YES);
    writeInstance->set_range(0, LONG_MAX);
    writeInstance->set_group(PUB);
    _parameterList["writeInstance"] = AnyParameter(writeInstance);

    ////////////////////////////////////////////////////////////////////////////
    //SUBSCRIBER PARAMETER
    Parameter<bool> * sub = new Parameter<bool>(false);
    sub->set_command_line_argument("-sub","");
    sub->set_description("Set test to be a subscriber");
    sub->set_type(T_BOOL);
    sub->set_extra_argument(NO);
    sub->set_group(SUB);
    _parameterList["sub"] = AnyParameter(sub);

    Parameter<int> *sidMultiSubTest = new Parameter<int>(0);
    sidMultiSubTest->set_command_line_argument("-sidMultiSubTest","<bytes>");
    sidMultiSubTest->set_description("Set the id of the subscriber in a\nmulti-subscriber test. Default: 0");
    sidMultiSubTest->set_type(T_NUMERIC_D);
    sidMultiSubTest->set_extra_argument(YES);
    sidMultiSubTest->set_range(0, INT_MAX);
    sidMultiSubTest->set_group(SUB);
    _parameterList["sidMultiSubTest"] = AnyParameter(sidMultiSubTest);

    Parameter<int> *numPublishers = new Parameter<int>(1);
    numPublishers->set_command_line_argument("-numPublishers","<count>");
    numPublishers->set_description("Number of publishers running in test.\nDefault: 1");
    numPublishers->set_type(T_NUMERIC_D);
    numPublishers->set_extra_argument(YES);
    numPublishers->set_range(1, ULLONG_MAX);
    numPublishers->set_group(SUB);
    _parameterList["numPublishers"] = AnyParameter(numPublishers);

    ParameterVector<unsigned long long> *cft = new ParameterVector<unsigned long long>();
    cft->set_command_line_argument("-cft","<start>:<end>");
    cft->set_description("Use a Content Filtered Topic for the Throughput topic in the\nsubscriber side. Specify 2 parameters: <start> and <end> to\nreceive samples with a key in that range.\nSpecify only 1 parameter to receive samples with that exact key.\nDefault: Not set");
    cft->set_type(T_VECTOR_NUMERIC);
    cft->set_extra_argument(YES);
    cft->set_range(0, MAX_CFT_VALUE - 1);
    cft->set_parse_method(SPLIT);
    cft->set_group(SUB);
    _parameterList["cft"] = AnyParameter(cft);

    ////////////////////////////////////////////////////////////////////////////
    // TRANSPORT PARAMETER:
    Parameter<std::string> *nic = new Parameter<std::string>();
    nic->set_command_line_argument("-nic","<ipaddr>");
    nic->set_description("Use only the nic specified by <ipaddr>.\nIf not specified, use all available interfaces");
    nic->set_type(T_STR);
    nic->set_extra_argument(YES);
    nic->set_group(TRANSPORT);
    _parameterList["nic"] = AnyParameter(nic);

    Parameter<std::string> *allowInterfaces = new Parameter<std::string>();
    allowInterfaces->set_command_line_argument("-allowInterfaces", "<ipaddr>");
    allowInterfaces->set_description("Use only the nic specified by <ipaddr>.\nIf not specified, use all available interfaces");
    allowInterfaces->set_type(T_STR);
    allowInterfaces->set_extra_argument(YES);
    allowInterfaces->set_group(TRANSPORT);
    allowInterfaces->set_internal(true);
    _parameterList["allowInterfaces"] = AnyParameter(allowInterfaces);

    ParameterVector<std::string> * peer = new ParameterVector<std::string>();
    peer->set_command_line_argument("-peer","<address>");
    peer->set_description("Adds a peer to the peer host address list.\nThis argument may be repeated to indicate multiple peers");
    peer->set_type(T_VECTOR_STR);
    peer->set_extra_argument(YES);
    peer->set_group(TRANSPORT);
    _parameterList["peer"] = AnyParameter(peer);

    Parameter<std::string> * transport = new Parameter<std::string>("Use XML");
    transport->set_command_line_argument("-transport","<kind>");
    transport->set_description("Set transport to be used. The rest of\nthe transports will be disabled.\nValues:\nUDPv4\nUDPv6\nSHMEM\nTCP\nTLS\nDTLS\nWAN\nUse XML\nDefault: Use XML (UDPv4|SHMEM)");
    transport->set_type(T_STR);
    transport->set_extra_argument(YES);
    transport->set_group(TRANSPORT);
    transport->add_valid_str_value("UDPv4");
    transport->add_valid_str_value("UDPv6");
    transport->add_valid_str_value("SHMEM");
    transport->add_valid_str_value("TCP");
    transport->add_valid_str_value("TLS");
    transport->add_valid_str_value("DTLS");
    transport->add_valid_str_value("WAN");
    _parameterList["transport"] = AnyParameter(transport);

    Parameter<bool> *multicast = new Parameter<bool>(false);
    multicast->set_command_line_argument("-multicast","");
    multicast->set_description("Use multicast to send data. Each topic\nwill use a different address\n\tlatency: '239.255.1.2'\n\tthroughput: '239.255.1.1'\n\tannouncement: '239.255.1.100'");
    multicast->set_type(T_BOOL);
    multicast->set_extra_argument(NO);
    multicast->set_group(TRANSPORT);
    _parameterList["multicast"] = AnyParameter(multicast);

    // TODO: set multicastAddrMap
    /*
     *  multicastAddrMap[THROUGHPUT_TOPIC_NAME] = argv[i];
     *  multicastAddrMap[LATENCY_TOPIC_NAME] = argv[i];
     *  multicastAddrMap[ANNOUNCEMENT_TOPIC_NAME] = argv[i];
     */
    /*
     * TODO: wait for merge the -multicastAddr option update
     * The parse for the input string will be done on the validation. After that
     * parameter manager does not will be called again.
     */
    Parameter<std::string> * multicastAddr = new Parameter<std::string>();
    multicastAddr->set_command_line_argument("-multicastAddr","<address>");
    multicastAddr->set_description("Use multicast to send data and set\nthe input <address> as the multicast\naddress for all the topics");
    multicastAddr->set_type(T_STR);
    multicastAddr->set_extra_argument(YES);
    multicastAddr->set_group(TRANSPORT);
    _parameterList["multicastAddr"] = AnyParameter(multicastAddr);

    Parameter<std::string> *transportVerbosity = new Parameter<std::string>();
    transportVerbosity->set_command_line_argument("-transportVerbosity","<level>");
    transportVerbosity->set_description("Verbosity of the transport.\nDefault: 0 (errors only)");
    transportVerbosity->set_type(T_STR);
    transportVerbosity->set_extra_argument(YES);
    transportVerbosity->set_group(TRANSPORT);
    _parameterList["transportVerbosity"] = AnyParameter(transportVerbosity);

    Parameter<std::string> * transportServerBindPort = new Parameter<std::string>("7400");
    transportServerBindPort->set_command_line_argument("-transportServerBindPort","<p>");
    transportServerBindPort->set_description("Port used by the transport to accept\nTCP/TLS connections <optional>.\nDefault: 7400");
    transportServerBindPort->set_type(T_STR);
    transportServerBindPort->set_extra_argument(YES);
    transportServerBindPort->set_group(TRANSPORT);
    _parameterList["transportServerBindPort"] = AnyParameter(transportServerBindPort);

    Parameter<bool> *transportWan = new Parameter<bool>(false);
    transportWan->set_command_line_argument("-transportWan","");
    transportWan->set_description("Use TCP/TLS across LANs and Firewalls.\nDefault: Not Set, LAN mode");
    transportWan->set_type(T_BOOL);
    transportWan->set_extra_argument(NO);
    transportWan->set_group(TRANSPORT);
    _parameterList["transportWan"] = AnyParameter(transportWan);

    Parameter<std::string> * transportPublicAddress = new Parameter<std::string>();
    transportPublicAddress->set_command_line_argument("-transportPublicAddress","<ip>");
    transportPublicAddress->set_description("Public IP address and port (WAN address\nand port) (separated with ‘:’ ) related\nto the transport instantiation. This is\nrequired when using server mode.\nDefault: Not Set");
    transportPublicAddress->set_type(T_STR);
    transportPublicAddress->set_extra_argument(YES);
    transportPublicAddress->set_group(TRANSPORT);
    _parameterList["transportPublicAddress"] = AnyParameter(transportPublicAddress);

    Parameter<std::string> * transportWanServerAddress = new Parameter<std::string>();
    transportWanServerAddress->set_command_line_argument("-transportWanServerAddress","<a>");
    transportWanServerAddress->set_description("Address where to find the WAN Server\nDefault: Not Set (Required)\n");
    transportWanServerAddress->set_type(T_STR);
    transportWanServerAddress->set_extra_argument(YES);
    transportWanServerAddress->set_group(TRANSPORT);
    _parameterList["transportWanServerAddress"] = AnyParameter(transportWanServerAddress);

    Parameter<std::string> * transportWanServerPort = new Parameter<std::string>("3478");
    transportWanServerPort->set_command_line_argument("-transportWanServerPort","<p>");
    transportWanServerPort->set_description("Port where to find the WAN Server.\nDefault: 3478");
    transportWanServerPort->set_type(T_STR);
    transportWanServerPort->set_extra_argument(YES);
    transportWanServerPort->set_group(TRANSPORT);
    _parameterList["transportWanServerPort"] = AnyParameter(transportWanServerPort);

    Parameter<std::string> *transportWanId = new Parameter<std::string>();
    transportWanId->set_command_line_argument("-transportWanId","<id>");
    transportWanId->set_description("Id to be used for the WAN transport.\nDefault: Not Set (Required)");
    transportWanId->set_type(T_STR);
    transportWanId->set_extra_argument(YES);
    transportWanId->set_group(TRANSPORT);
    _parameterList["transportWanId"] = AnyParameter(transportWanId);

    Parameter<bool> *transportSecureWan = new Parameter<bool>(false);
    transportSecureWan->set_command_line_argument("-transportSecureWan","");
    transportSecureWan->set_description("Use WAN with security.\nDefault: False");
    transportSecureWan->set_type(T_BOOL);
    transportSecureWan->set_extra_argument(NO);
    transportSecureWan->set_group(TRANSPORT);
    _parameterList["transportSecureWan"] = AnyParameter(transportSecureWan);

    Parameter<std::string> * transportCertAuthority = new Parameter<std::string>(TRANSPORT_CERTAUTHORITY_FILE);
    transportCertAuthority->set_command_line_argument("-transportCertAuthority","<file>");
    transportCertAuthority->set_description("Certificate authority file <optional>.\nDefault: \"" + TRANSPORT_CERTAUTHORITY_FILE + "\"");
    transportCertAuthority->set_type(T_STR);
    transportCertAuthority->set_extra_argument(YES);
    transportCertAuthority->set_group(TRANSPORT);
    _parameterList["transportCertAuthority"] = AnyParameter(transportCertAuthority);

    Parameter<std::string> * transportCertFile = new Parameter<std::string>(TRANSPORT_CERTIFICATE_FILE_PUB);
    transportCertFile->set_command_line_argument("-transportCertFile","<file>");
    transportCertFile->set_description("Certificate file <optional>.\nDefault (Publisher): \"" + TRANSPORT_CERTIFICATE_FILE_PUB + "\"\nDefault (Subscriber): \"" + TRANSPORT_CERTIFICATE_FILE_SUB + "\"\n");
    transportCertFile->set_type(T_STR);
    transportCertFile->set_extra_argument(YES);
    transportCertFile->set_group(TRANSPORT);
    _parameterList["transportCertFile"] = AnyParameter(transportCertFile);

    Parameter<std::string> * transportPrivateKey = new Parameter<std::string>(TRANSPORT_CERTIFICATE_FILE_PUB);
    transportPrivateKey->set_command_line_argument("-transportPrivateKey","<file>");
    transportPrivateKey->set_description("Private key file <optional>.\nDefault (Publisher): \"" + TRANSPORT_PRIVATEKEY_FILE_PUB + "\"\nDefault (Subscriber): \"" + TRANSPORT_PRIVATEKEY_FILE_SUB + "\"\n");
    transportPrivateKey->set_type(T_STR);
    transportPrivateKey->set_extra_argument(YES);
    transportPrivateKey->set_group(TRANSPORT);
    _parameterList["transportPrivateKey"] = AnyParameter(transportPrivateKey);

    ////////////////////////////////////////////////////////////////////////////
    // SECURE PARAMETER:
  #ifdef RTI_SECURE_PERFTEST
    Parameter<bool> *secureEncryptDiscovery = new Parameter<bool>(false);
    secureEncryptDiscovery->set_command_line_argument("-secureEncryptDiscovery","");
    secureEncryptDiscovery->set_description("Encrypt discovery traffic");
    secureEncryptDiscovery->set_type(T_BOOL);
    secureEncryptDiscovery->set_extra_argument(NO);
    secureEncryptDiscovery->set_group(SECURE);
    _parameterList["secureEncryptDiscovery"] = AnyParameter(secureEncryptDiscovery);

    Parameter<bool> *secureSign = new Parameter<bool>(false);
    secureSign->set_command_line_argument("-secureSign","");
    secureSign->set_description("Sign (HMAC) discovery and user data");
    secureSign->set_type(T_BOOL);
    secureSign->set_extra_argument(NO);
    secureSign->set_group(SECURE);
    _parameterList["secureSign"] = AnyParameter(secureSign);

    Parameter<bool> *secureEncryptBoth = new Parameter<bool>(false);
    secureEncryptBoth->set_command_line_argument("-secureEncryptBoth","");
    secureEncryptBoth->set_description("Sign (HMAC) discovery and user data");
    secureEncryptBoth->set_type(T_BOOL);
    secureEncryptBoth->set_extra_argument(NO);
    secureEncryptBoth->set_group(SECURE);
    _parameterList["secureEncryptBoth"] = AnyParameter(secureEncryptBoth);

    Parameter<bool> *secureEncryptData = new Parameter<bool>(false);
    secureEncryptData->set_command_line_argument("-secureEncryptData","");
    secureEncryptData->set_description("Encrypt topic (user) data");
    secureEncryptData->set_type(T_BOOL);
    secureEncryptData->set_extra_argument(NO);
    secureEncryptData->set_group(SECURE);
    _parameterList["secureEncryptData"] = AnyParameter(secureEncryptData);

    Parameter<bool> *secureEncryptSM = new Parameter<bool>(false);
    secureEncryptSM->set_command_line_argument("-secureEncryptSM","");
    secureEncryptSM->set_description("Encrypt RTPS submessages");
    secureEncryptSM->set_type(T_BOOL);
    secureEncryptSM->set_extra_argument(NO);
    secureEncryptSM->set_group(SECURE);
    _parameterList["secureEncryptSM"] = AnyParameter(secureEncryptSM);

    Parameter<std::string> *secureGovernanceFile = new Parameter<std::string>();
    secureGovernanceFile->set_command_line_argument("-secureGovernanceFile","<file>");
    secureGovernanceFile->set_description("Governance file. If specified, the authentication,\nsigning, and encryption arguments are ignored. The\ngovernance document configuration will be used instead.\nDefault: built using the secure options");
    secureGovernanceFile->set_type(T_STR);
    secureGovernanceFile->set_extra_argument(YES);
    secureGovernanceFile->set_group(SECURE);
    _parameterList["secureGovernanceFile"] = AnyParameter(secureGovernanceFile);

    Parameter<std::string> *securePermissionsFile = new Parameter<std::string>();
    securePermissionsFile->set_command_line_argument("-securePermissionsFile","<file>");
    securePermissionsFile->set_description("Permissions file <optional>.\nDefault: \"./resource/secure/signed_PerftestPermissionsSub.xml\"");
    securePermissionsFile->set_type(T_STR);
    securePermissionsFile->set_extra_argument(YES);
    securePermissionsFile->set_group(SECURE);
    _parameterList["securePermissionsFile"] = AnyParameter(securePermissionsFile);

    Parameter<std::string> *secureCertAuthority = new Parameter<std::string>();
    secureCertAuthority->set_command_line_argument("-secureCertAuthority","<file>");
    secureCertAuthority->set_description("Certificate authority file <optional>.\nDefault: \"./resource/secure/cacert.pem\"");
    secureCertAuthority->set_type(T_STR);
    secureCertAuthority->set_extra_argument(YES);
    secureCertAuthority->set_group(SECURE);
    _parameterList["secureCertAuthority"] = AnyParameter(secureCertAuthority);

    Parameter<std::string> *secureCertFile = new Parameter<std::string>();
    secureCertFile->set_command_line_argument("-secureCertFile","<file>");
    secureCertFile->set_description("Certificate file <optional>.\nDefault: \"./resource/secure/sub.pem\"");
    secureCertFile->set_type(T_STR);
    secureCertFile->set_extra_argument(YES);
    secureCertFile->set_group(SECURE);
    _parameterList["secureCertFile"] = AnyParameter(secureCertFile);

    Parameter<std::string> *securePrivateKey = new Parameter<std::string>();
    securePrivateKey->set_command_line_argument("-securePrivateKey","<file>");
    securePrivateKey->set_description("Private key file <optional>.\nDefault: \"./resource/secure/subkey.pem\"");
    securePrivateKey->set_type(T_STR);
    securePrivateKey->set_extra_argument(YES);
    securePrivateKey->set_group(SECURE);
    _parameterList["securePrivateKey"] = AnyParameter(securePrivateKey);

    Parameter<std::string> *secureLibrary = new Parameter<std::string>();
    secureLibrary->set_command_line_argument("-secureLibrary","<file>");
    secureLibrary->set_description("Private key file <optional>.\nDefault: \"./resource/secure/subkey.pem\"");
    secureLibrary->set_type(T_STR);
    secureLibrary->set_extra_argument(YES);
    secureLibrary->set_group(SECURE);
    _parameterList["secureLibrary"] = AnyParameter(secureLibrary);

    Parameter<int> *secureDebug = new Parameter<int>(1);
    secureDebug->set_command_line_argument("-secureDebug","<level>");
    secureDebug->set_type(T_NUMERIC_D);
    secureDebug->set_extra_argument(YES);
    secureDebug->set_range(0, 7);
    secureDebug->set_group(SECURE);
    secureDebug->set_internal(true);
    _parameterList["secureDebug"] = AnyParameter(secureDebug);

#endif
}


// Parse the command line parameters and set the value
bool ParameterManager::parse(int argc, char *argv[])
{
    unsigned long long varLLU;
    long varLD;
    int varD;
    bool success = true;
    ParameterBase *p = NULL;
    // Copy all arguments into a container of strings
    std::vector<std::string> allArgs(argv, argv + argc);
    std::map<std::string, AnyParameter>::iterator it;

    for (unsigned int i = 1; i < allArgs.size(); i++) {
        for (it = _parameterList.begin(); it != _parameterList.end(); it++) {
            if (IS_OPTION(allArgs[i].c_str(), it->second.get()->get_option().c_str())) {
                p = it->second.get(); // Save the variable, it will be used several time.
                // NumArguments == 0
                if (p->get_extra_argument() == NO) {
                    // Type is T_BOOL
                    if (p->get_type() == T_BOOL) {
                        (static_cast<Parameter<bool>*>(it->second.get<bool>()))->set_value(true);
                    }
                // NumArguments is 1 or optional
                } else { // if (p->get_extra_argument() > NO) {
                    // Check for error in the number of arguments
                    if (i + 1 >= allArgs.size() || allArgs[i + 1].find("-") == 0) {
                        if (p->get_extra_argument() == YES) {
                            fprintf(stderr, "Missing '%s' after '%s'\n",
                                p->get_arg().c_str(),
                                p->get_option().c_str());
                            return false;
                        } else if (p->get_extra_argument() == OPTIONAL) {
                            p->set_isSet(true);
                            break;
                        }
                    }
                    ++i;
                    // Type is T_STR
                    if (p->get_type() == T_STR) {
                        if (!p->validate_str_range(allArgs[i])) {
                            success = false;
                        }
                        (static_cast<Parameter<std::string>*>(it->second.get<std::string>()))->set_value(allArgs[i]);
                    }
                    // Type is T_NUMERIC_LLU
                    else if (p->get_type() == T_NUMERIC_LLU) {
                        if (sscanf(allArgs[i].c_str(), "%llu", &varLLU) != 1) {
                            fprintf(stderr, "Cannot parse '%s' '%s', invalid input.\n",
                                    p->get_arg().c_str(),
                                    p->get_option().c_str());
                            success = false;
                        }
                        if (!p->validate_numeric_range(varLLU)) {
                            success = false;
                        }
                        (static_cast<Parameter<unsigned long long>*>(it->second.get<unsigned long long>()))->set_value(varLLU);
                    }
                    // Type is T_NUMERIC_LD
                    else if (p->get_type() == T_NUMERIC_LD) {
                        if (sscanf(allArgs[i].c_str(), "%ld", &varLD) != 1) {
                            fprintf(stderr, "Cannot parse '%s' '%s', invalid input.\n",
                                    p->get_arg().c_str(),
                                    p->get_option().c_str());
                            success = false;
                        }
                        if (!p->validate_numeric_range(varLD)) {
                            success = false;
                        }
                        (static_cast<Parameter<long>*>(it->second.get<long>()))->set_value(varLD);
                    }
                    // Type is T_NUMERIC_D
                    else if (p->get_type() == T_NUMERIC_D) {
                        if (sscanf(allArgs[i].c_str(), "%d", &varD) != 1) {
                            fprintf(stderr, "Cannot parse '%s' '%s', invalid input.\n",
                                    p->get_arg().c_str(),
                                    p->get_option().c_str());
                            success = false;
                        }
                        if (!p->validate_numeric_range(varD)) {
                            success = false;
                        }
                        (static_cast<Parameter<int>*>(it->second.get<int>()))->set_value(varD);
                    }
                    // Type is T_VECTOR_STR
                    else if (p->get_type() == T_VECTOR_STR) {
                        if (NOSPLIT == ((ParameterVector<std::string>*)it->second.get_vector<std::string>())->get_parse_method()) {
                            if (!p->validate_str_range(allArgs[i])) {
                                success = false;
                            }
                            (static_cast<ParameterVector<std::string>*>(it->second.get_vector<std::string>()))->set_value(allArgs[i]);
                        }
                    }
                    // Type is T_VECTOR_NUMERIC
                    else if (p->get_type() == T_VECTOR_NUMERIC) {
                        if (SPLIT == ((ParameterVector<unsigned long long>*)it->second.get_vector<unsigned long long>())->get_parse_method()) {
                            std::vector<std::string> v = split(allArgs[i]);
                            for (unsigned int j = 0; j < v.size(); j++) {
                                if (sscanf(v[j].c_str(), "%llu", &varLLU) != 1) {
                                    fprintf(stderr, "Cannot parse '%s' '%s', invalid input.\n",
                                            p->get_arg().c_str(),
                                            p->get_option().c_str());
                                    success = false;
                                }
                                if (!p->validate_numeric_range(varLLU)) {
                                    success = false;
                                }
                                (static_cast<ParameterVector<unsigned long long>*>(it->second.get_vector<unsigned long long>()))->set_value(varLLU);
                            }
                        }
                    }
                    // Type is T_PAIR_NUMERIC_STR
                    else if (p->get_type() == T_PAIR_NUMERIC_STR) {
                        std::vector<std::string> v = split(allArgs[i]);
                        if (v.size() != 2) {
                            fprintf(stderr, "Missing '%s' after '%s'\n",
                                p->get_arg().c_str(),
                                p->get_option().c_str());
                            return false;
                        } else {
                            if (sscanf(v[0].c_str(), "%llu", &varLLU) != 1) {
                                fprintf(stderr, "Cannot parse '%s' '%s', invalid input.\n",
                                        p->get_arg().c_str(),
                                        p->get_option().c_str());
                                success = false;
                            }
                            if (!p->validate_numeric_range(varLLU)) {
                                success = false;
                            }
                            if (!p->validate_str_range(v[1])) {
                                success = false;
                            }
                            (static_cast<ParameterPair<unsigned long long, std::string>*>(it->second.get_pair<unsigned long long, std::string>()))->set_value(varLLU, v[1]);
                        }
                    }
                }
                break;
            }
        }
        if (it == _parameterList.end()) {
            fprintf(stderr, "Cannot parse '%s', invalid input.\n",
                    allArgs[i].c_str());
            success = false;
        }
    }
    return success;
}

// Get the help message
std::string ParameterManager::display_help()
{
    std::map<std::string, AnyParameter>::iterator it;
    std::ostringstream oss;
    std::map<GROUP, std::string> output;
    for (unsigned int i = GENERAL; i != RAWTRANSPORT + 1; i++) {
        switch (static_cast<GROUP>(i)) {
            case GENERAL:
                output[static_cast<GROUP>(i)] += get_center_header_help_line("GENERAL");
                break;
            case PUB:
                output[static_cast<GROUP>(i)] += get_center_header_help_line("PUBLISHER");
                break;
            case SUB:
                output[static_cast<GROUP>(i)] += get_center_header_help_line("SUBSCRIBER");
                break;
            case TRANSPORT:
                output[static_cast<GROUP>(i)] += get_center_header_help_line("TRANSPORT");
                break;
          #ifdef RTI_SECURE_PERFTEST
            case SECURE:
                output[static_cast<GROUP>(i)] += get_center_header_help_line("SECURE");
                break;
          #endif
            case RAWTRANSPORT:
                output[static_cast<GROUP>(i)] += get_center_header_help_line("RAWTRANSPORT");
                break;
            default:
                break;
        }
    }

    oss << "/**********************************************************************************************/\n"
        << "Usage:\t perftest_cpp [options]\n"
        << "Where [options] are:\n";
    output[GENERAL] +="\t-help                           - Print this usage message and exit\n";

    for (it = _parameterList.begin(); it != _parameterList.end(); it++) {
        if (!it->second.get()->get_internal()) {
            output[it->second.get()->get_group()] +=
                    it->second.get()->print_command_line_parameter();
        }
    }
    std::map<GROUP, std::string>::iterator itOutput;
    for (itOutput = output.begin(); itOutput != output.end(); itOutput++) {
        oss << itOutput->second;
    }
    oss << "/**********************************************************************************************/\n";
    return oss.str();
}

// check for the '-help' option
bool ParameterManager::check_help(int argc, char *argv[])
{
    std::vector<std::string> allArgs(argv, argv + argc);
    for (unsigned int i = 1; i < allArgs.size(); i++) {
        if (allArgs[i] == "-help" || allArgs[i] == "-h") {
            std::cout << display_help() <<'\n';
            return true;
        }
    }
    return false;
}

ParameterManager::~ParameterManager()
{
    _parameterList.clear();
}

// check if a variable has been set
bool ParameterManager::is_set(std::string parameterKey)
{
    std::map<std::string, AnyParameter>::iterator it =
            _parameterList.find(parameterKey);
    if (it != _parameterList.end()) {
        return it->second.get()->get_isSet();
    } else {
        return false;
    }
}


bool ParameterManager::validate_group()
{
    bool success = true;
    std::map<std::string, AnyParameter>::iterator it;
    for (it = _parameterList.begin(); it != _parameterList.end(); it++) {
        if (it->second.get()->get_isSet()) {
            if (it->second.get()->get_group() == PUB && GetInstance().get<bool>("sub")) {
                fprintf(stderr, "Cannot use '%s' while setting '-sub'.\n",
                        it->second.get()->get_option().c_str());
                success = false;
            } else if (it->second.get()->get_group() == SUB && GetInstance().get<bool>("pub")) {
                fprintf(stderr, "Cannot use '%s' while setting '-pub'.\n",
                        it->second.get()->get_option().c_str());
                success = false;
            }
        }
    }
    return success;
}


std::vector<std::string> ParameterManager::split(std::string var, std::string delimiter)
{
    std::vector<std::string> v;
    char *pch;
    char *str = new char[var.length() + 1];
    strcpy(str, var.c_str());
    pch = strtok (str, delimiter.c_str());
    while (pch != NULL) {
        v.push_back(pch);
        pch = strtok (NULL, delimiter.c_str());
    }
    delete[] str;
    return v;
}

std::string ParameterManager::get_center_header_help_line(std::string name)
{
    name += " Specific Options";
    std::stringstream line;
    unsigned int maxWithLine = 80;
    std::string separatorBar =
            std::string((int) ((maxWithLine - name.length() - 2) / 2), '=');
    line << "\n\n\t" << separatorBar << " " << name << " " << separatorBar << "\n\n";
    if (line.str().length() < maxWithLine) { //If name is odd, then add one more '='
        line << '=';
    }
    return line.str();
}

bool ParameterManager::group_is_use(GROUP group)
{
    std::map<std::string, AnyParameter>::iterator it;
    for (it = _parameterList.begin(); it != _parameterList.end(); it++) {
        if (it->second.get()->get_isSet() && it->second.get()->get_group() == group) {
            return true;
        }
    }
    return false;
}