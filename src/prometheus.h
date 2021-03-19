#ifndef BITCOIN_PROMETHEUS_H
#define BITCOIN_PROMETHEUS_H
#include <string>
#include <functional>
#include <chrono>
#include <map>
#include <memory>
#include <thread>
#include <prometheus/counter.h>
#include <prometheus/exposer.h>
#include <prometheus/registry.h>


static const int DEFAULT_PROMSERVER_THREADS=4;
static const std::string DEFAULT_PROMSERVER_BIND="127.0.0.1:9153";
static const bool DEFAULT_PROMSERVER = true;
inline bool STOP_PROMSERVER_THREAD = false;


void StartPrometheus();
inline auto registry = std::make_shared<prometheus::Registry>();

/* ***************************** */
/* counters */
/* ***************************** */
inline auto& bandwidth_bytes_received_total = prometheus::BuildCounter()
    .Name("btc_bandwidth_bytes_received_total")
    .Help("Total Received Bandwidth in bytes")
    .Register(*registry);
inline auto& bandwidth_bytes_sent_total = prometheus::BuildCounter()
    .Name("btc_bandwidth_bytes_sent_total")
    .Help("Total Sent Bnadwidth in bytes")
    .Register(*registry);
inline auto& bandwidth_message_bytes_received_total = prometheus::BuildCounter()
    .Name("btc_bandwidth_message_bytes_received_total")
    .Help("Total Received Message Bandwidth in bytes")
    .Register(*registry);
inline auto& bandwidth_message_bytes_sent_total = prometheus::BuildCounter()
    .Name("btc_bandwidth_message_bytes_sent_total")
    .Help("Total Sent Message Bandwidth in bytes")
    .Register(*registry);
inline auto& message_received = prometheus::BuildCounter()
    .Name("btc_message_received")
    .Help("Count of Messages Received")
    .Register(*registry);
inline auto& message_sent = prometheus::BuildCounter()
    .Name("btc_message_sent")
    .Help("Count of Messages Sent")
    .Register(*registry);
inline auto& misbehavior_banned = prometheus::BuildCounter()
    .Name("btc_misbehavior_banned")
    .Help("Count of Banned Peers")
    .Register(*registry);
inline auto& transactions_accepted = prometheus::BuildCounter()
    .Name("btc_transactions_accepted")
    .Help("Count of Transactions Accepted")
    .Register(*registry);
inline auto& transactions_fees = prometheus::BuildCounter()
    .Name("btc_transactions_fees")
    .Help("Current Transaction Fees ")
    .Register(*registry);
inline auto& transactions_input_value = prometheus::BuildCounter()
    .Name("btc_transactions_input_value")
    .Help("Current Transaction Input Value")
    .Register(*registry);
inline auto& transactions_inputs = prometheus::BuildCounter()
    .Name("btc_transactions_inputs")
    .Help("Current Transaction Input")
    .Register(*registry);
inline auto& transactions_output_value = prometheus::BuildCounter()
    .Name("btc_transactions_output_value")
    .Help("Current Transaction Output Value")
    .Register(*registry);
inline auto& transactions_outputs = prometheus::BuildCounter()
    .Name("btc_transactions_outputs")
    .Help("Current Transaction Output")
    .Register(*registry);
inline auto& transactions_sig_ops = prometheus::BuildCounter()
    .Name("btc_transactions_sig_ops")
    .Help("Current Transaction SigOps")
    .Register(*registry);
inline auto& transactions_size_bytes = prometheus::BuildCounter()
    .Name("btc_transactions_size_bytes")
    .Help("Transaction Size in Bytes")
    .Register(*registry);
inline auto& warnings_invalid_block = prometheus::BuildCounter()
    .Name("btc_warnings_invalid_block")
    .Help("Count of Invalid Block Warning")
    .Register(*registry);
inline auto& bandwidth_message_bytes_received = prometheus::BuildCounter()
    .Name("btc_bandwidth_message_bytes_received")
    .Help("Bandwidth Received Messages in bytes")
    .Register(*registry);
inline auto& bandwidth_message_bytes_sent = prometheus::BuildCounter()
    .Name("btc_bandwidth_message_bytes_sent")
    .Help("Bandwidth Sent Messages in bytes")
    .Register(*registry);

inline auto& BandwidthBytesReceivedTotal = bandwidth_bytes_received_total.Add({});
inline auto& BandwidthBytesSentTotal = bandwidth_bytes_sent_total.Add({});
inline auto& MisbehaviorBanned = misbehavior_banned.Add({});
inline auto& TransactionsAccepted = transactions_accepted.Add({});
inline auto& TransactionsFees = transactions_fees.Add({});
inline auto& TransactionsInputs = transactions_inputs.Add({});
inline auto& TransactionsInputValue = transactions_input_value.Add({});
inline auto& TransactionsOutputs = transactions_outputs.Add({});
inline auto& TransactionsOutputValue = transactions_output_value.Add({});
inline auto& TransactionsSigOps = transactions_sig_ops.Add({});
inline auto& TransactionsSizeBytes = transactions_size_bytes.Add({});
inline auto& WarningsInvalidBlock = warnings_invalid_block.Add({});
inline auto& BandwidthMessageBytesReceived = bandwidth_message_bytes_received.Add({});
inline auto& BandwidthMessageBytesSent = bandwidth_message_bytes_sent.Add({});

/* ***************************** */


/* ***************************** */
/* gauges */
/* ***************************** */
inline auto& accept_to_memory_pool_ms = prometheus::BuildGauge()
    .Name("btc_accept_to_memory_pool_ms")
    .Help("Time to accept to memory pool in ms")
    .Register(*registry);
inline auto& activate_best_chain_ms = prometheus::BuildGauge()
    .Name("btc_activate_best_chain_ms")
    .Help("Time to activate best chain in ms")
    .Register(*registry);
inline auto& activate_block_ms = prometheus::BuildGauge()
    .Name("btc_activate_block_ms")
    .Help("Time to activate block in ms")
    .Register(*registry);
inline auto& bandwidth_bytes_received = prometheus::BuildGauge()
    .Name("btc_bandwidth_bytes_received")
    .Help("Bandwidth Received in bytes")
    .Register(*registry);
inline auto& bandwidth_bytes_sent = prometheus::BuildGauge()
    .Name("btc_badwidth_bytes_sent")
    .Help("Bandwidth Received in bytes")
    .Register(*registry);
inline auto& block_height = prometheus::BuildGauge()
    .Name("btc_block_height")
    .Help("Block Height")
    .Register(*registry);
inline auto& block_num_transations = prometheus::BuildGauge()
    .Name("btc_block_num_transations")
    .Help("Count of Transactions")
    .Register(*registry);
inline auto& block_sigops = prometheus::BuildGauge()
    .Name("btc_block_sigops")
    .Help("Count of SigOps")
    .Register(*registry);
inline auto& block_size_bytes = prometheus::BuildGauge()
    .Name("btc_block_current_size_bytes")
    .Help("Current block size in bytes")
    .Register(*registry);
inline auto& block_size_witness_bytes = prometheus::BuildGauge()
    .Name("btc_block_current_size_witness_bytes")
    .Help("Current witness block size in bytes")
    .Register(*registry);
inline auto& block_version = prometheus::BuildGauge()
    .Name("btc_block_version")
    .Help("Current Block Version")
    .Register(*registry);
inline auto& block_weight = prometheus::BuildGauge()
    .Name("btc_block_weight")
    .Help("Current Block Weight")
    .Register(*registry);
inline auto& check_block_us = prometheus::BuildGauge()
    .Name("btc_check_block_us")
    .Help("Time to check block in us")
    .Register(*registry);
inline auto& check_inputs_ms = prometheus::BuildGauge()
    .Name("btc_check_inputs_ms")
    .Help("Time to check inputs in ms")
    .Register(*registry);
inline auto& check_transaction_us = prometheus::BuildGauge()
    .Name("btc_check_transaction_us")
    .Help("Time to check transactions in us")
    .Register(*registry);
inline auto& connect_block_ms = prometheus::BuildGauge()
    .Name("btc_connect_block_ms")
    .Help("Time to connect block in ms")
    .Register(*registry);
inline auto& connect_tip_ms = prometheus::BuildGauge()
    .Name("btc_connect_tip_ms")
    .Help("Time to connect tip in ms")
    .Register(*registry);
inline auto& disconnect_block_ms = prometheus::BuildGauge()
    .Name("btc_disconnect_block_ms")
    .Help("time to disconnect block in ms")
    .Register(*registry);
inline auto& fee_name = prometheus::BuildGauge()
    .Name("btc_fee_name")
    .Help("Fee Estimage")
    .Register(*registry);
inline auto& message_received_inv_block = prometheus::BuildGauge()
    .Name("btc_message_received_inv_block")
    .Help("Count of inv block messages")
    .Register(*registry);
inline auto& message_received_inv_tx = prometheus::BuildGauge()
    .Name("btc_message_received_inv_tx")
    .Help("Count of inv tx messages")
    .Register(*registry);
inline auto& misbehavior_amount = prometheus::BuildGauge()
    .Name("btc_misbehavior_amount")
    .Help("Misbehavior Amount")
    .Register(*registry);
inline auto& network_difficulty = prometheus::BuildGauge()
    .Name("btc_network_difficulty")
    .Help("Current Network Difficulty")
    .Register(*registry);
inline auto& network_exahashes_per_second = prometheus::BuildGauge()
    .Name("btc_network_exahashes_per_second")
    .Help("Current network exahashes per second")
    .Register(*registry);
inline auto& peers_connect = prometheus::BuildGauge()
    .Name("btc_peers_connect")
    .Help("Current peers connected")
    .Register(*registry);
inline auto& peers_disconnect = prometheus::BuildGauge()
    .Name("btc_peers_disconnect")
    .Help("Current peers disconnected")
    .Register(*registry);
inline auto& peers_full_node_connections = prometheus::BuildGauge()
    .Name("btc_peers_full_node_connections")
    .Help("Current Peers connected as full node")
    .Register(*registry);
inline auto& peers_inbound_connections = prometheus::BuildGauge()
    .Name("btc_peers_inbound_connections")
    .Help("Current inbound connections")
    .Register(*registry);
inline auto& peers_ipv4_connections = prometheus::BuildGauge()
    .Name("btc_peers_ipv4_connections")
    .Help("Current IPv4 connections")
    .Register(*registry);
inline auto& peers_ipv6_connections = prometheus::BuildGauge()
    .Name("btc_peers_ipv6_connections")
    .Help("Current IPv6 connections")
    .Register(*registry);
inline auto& peers_known_addresses = prometheus::BuildGauge()
    .Name("btc_peers_known_addresses")
    .Help("Current known peer addresses")
    .Register(*registry);
inline auto& peers_outbound_connections = prometheus::BuildGauge()
    .Name("btc_peers_outbound_connections")
    .Help("Current outputbound peer connections")
    .Register(*registry);
inline auto& peers_ping_us = prometheus::BuildGauge()
    .Name("btc_peers_ping_us")
    .Help("Current peer ping time in us")
    .Register(*registry);
inline auto& peers_spv_node_connections = prometheus::BuildGauge()
    .Name("btc_peers_spv_node_connections")
    .Help("Current spv connections")
    .Register(*registry);
inline auto& peers_tor_connections = prometheus::BuildGauge()
    .Name("btc_peers_tor_connections")
    .Help("Current TOR connections")
    .Register(*registry);
inline auto& peers_total_connections = prometheus::BuildGauge()
    .Name("btc_peers_total_connections")
    .Help("Current total peer connections")
    .Register(*registry);
inline auto& transactions_duplicate = prometheus::BuildGauge()
    .Name("btc_transactions_duplicate")
    .Help("Current duplicate transactions")
    .Register(*registry);
inline auto& transactions_mempool_memory_usage_bytes = prometheus::BuildGauge()
    .Name("btc_transactions_mempool_memory_usage_bytes")
    .Help("Current tx mempoool memory usage in bytes")
    .Register(*registry);
inline auto& transactions_mempool_min_free = prometheus::BuildGauge()
    .Name("btc_transactions_mempool_min_free_per_kb")
    .Help("Current tx mempoool memory min free in kb")
    .Register(*registry);
inline auto& transactions_mempool_total_transactions = prometheus::BuildGauge()
    .Name("btc_transactions_mempool_total_transactions")
    .Help("Current Transactions in mempool")
    .Register(*registry);
inline auto& transactions_mempool_total_tx_bytes = prometheus::BuildGauge()
    .Name("btc_transactions_mempool_total_tx_bytes")
    .Help("Current transactions in mempool in bytes")
    .Register(*registry);
inline auto& transactions_orphans = prometheus::BuildGauge()
    .Name("btc_transactions_orphans")
    .Help("Current oprhaned transactions")
    .Register(*registry);
inline auto& transactions_orphans_add = prometheus::BuildGauge()
    .Name("btc_transactions_orphans_add")
    .Help("Current added orphaned transactions")
    .Register(*registry);
inline auto& transactions_orphans_remove = prometheus::BuildGauge()
    .Name("btc_transactions_orphans_remove")
    .Help("Current removed orphaned transactions")
    .Register(*registry);
inline auto& transactions_tx_cache_size = prometheus::BuildGauge()
    .Name("btc_transactions_tx_cache_size")
    .Help("Current transaction tx cache size")
    .Register(*registry);
inline auto& transactions_tx_in_memory_pool = prometheus::BuildGauge()
    .Name("btc_transactions_tx_in_memory_pool")
    .Help("Current transactions in mempool")
    .Register(*registry);
inline auto& utxoset_block_height = prometheus::BuildGauge()
    .Name("btc_utxoset_block_height")
    .Help("Current utxoset block height")
    .Register(*registry);
inline auto& utxoset_db_size_bytes = prometheus::BuildGauge()
    .Name("btc_utxoset_db_size_bytes")
    .Help("Current utxoset db size in bytes")
    .Register(*registry);
inline auto& utxoset_total_btc_amount = prometheus::BuildGauge()
    .Name("btc_utxoset_total_btc_amount")
    .Help("Current utxoset in btc")
    .Register(*registry);
inline auto& utxoset_tx = prometheus::BuildGauge()
    .Name("btc_utxoset_tx")
    .Help("Current utxoset tx")
    .Register(*registry);
inline auto& utxoset_tx_outputs = prometheus::BuildGauge()
    .Name("btc_utxoset_tx_outputs")
    .Help("Current utxoset tx outputs")
    .Register(*registry);
inline auto& transactions_total_count = prometheus::BuildGauge()
    .Name("btc_transactions_total_count")
    .Help("Current total transactions")
    .Register(*registry);
inline auto& transactions_tx_rate = prometheus::BuildGauge()
    .Name("btc_transactions_tx_rate")
    .Help("Current transaction rate")
    .Register(*registry);

inline auto& AcceptToMemoryPoolMs = accept_to_memory_pool_ms.Add({});
inline auto& ActivateBestChainMs = activate_best_chain_ms.Add({});
inline auto& ActivateBlockMs = activate_block_ms.Add({});
inline auto& BandwidthBytesReceived = bandwidth_bytes_received.Add({});
inline auto& BandwidthBytesSent = bandwidth_bytes_sent.Add({});
inline auto& BlockHeight = block_height.Add({});
inline auto& BlockNumTransactions = block_num_transations.Add({});
inline auto& BlockSigOps = block_sigops.Add({});
inline auto& BlockSizeBytes = block_size_bytes.Add({});
inline auto& BlockSizeWitnessBytes = block_size_witness_bytes.Add({});
inline auto& BlockVersion = block_version.Add({});
inline auto& BlockWeight = block_weight.Add({});
inline auto& CheckBlockUs = check_block_us.Add({});
inline auto& CheckInputsMs = check_inputs_ms.Add({});
inline auto& CheckTransactionUs = check_transaction_us.Add({});
inline auto& ConnectBlockMs = connect_block_ms.Add({});
inline auto& ConnectTipMs = connect_tip_ms.Add({});
inline auto& DisconnectBlockMs = disconnect_block_ms.Add({});
inline auto& FeeName = fee_name.Add({});
inline auto& MessageReceivedInvBlock = message_received_inv_block.Add({});
inline auto& MessageReceivedInvTx = message_received_inv_tx.Add({});
inline auto& MisbehaviorAmount = misbehavior_amount.Add({});
inline auto& NetworkDifficulty = network_difficulty.Add({});
inline auto& NetworkExahashesPerSecond = network_exahashes_per_second.Add({});
inline auto& PeersConnect = peers_connect.Add({});
inline auto& PeersDisconnect = peers_disconnect.Add({});
inline auto& PeersFullNodeConnections = peers_full_node_connections.Add({});
inline auto& PeersInboundConnections = peers_inbound_connections.Add({});
inline auto& PeersIpv4Connections = peers_ipv4_connections.Add({});
inline auto& PeersIpv6Connections = peers_ipv6_connections.Add({});
inline auto& PeersKnownAddresses = peers_known_addresses.Add({});
inline auto& PeersOutboundConnections = peers_outbound_connections.Add({});
inline auto& PeersPingUs = peers_ping_us.Add({});
inline auto& PeersSpvNodeConnections = peers_spv_node_connections.Add({});
inline auto& PeersTorConnections = peers_tor_connections.Add({});
inline auto& PeersTotalConnections = peers_total_connections.Add({});
inline auto& TransactionsDuplicate = transactions_duplicate.Add({});
inline auto& TransactionsMempoolMemoryUsageBytes = transactions_mempool_memory_usage_bytes.Add({});
inline auto& TransactionsMempoolMinFree = transactions_mempool_min_free.Add({});
inline auto& TransactionsMempoolTotalTransactions = transactions_mempool_total_transactions.Add({});
inline auto& TransactionsMempoolTotalTXBytes = transactions_mempool_total_tx_bytes.Add({});
inline auto& TransactionsOrphans = transactions_orphans.Add({});
inline auto& TransactionsOrphansAdd = transactions_orphans_add.Add({});
inline auto& TransactionsOrphansRemove = transactions_orphans_remove.Add({});
inline auto& TransactionsTXCacheSize = transactions_tx_cache_size.Add({});
inline auto& TransactionsTxInMemoryPool = transactions_tx_in_memory_pool.Add({});
inline auto& UtxosetBlockHeight = utxoset_block_height.Add({});
inline auto& UtxosetDbSizeBytes = utxoset_db_size_bytes.Add({});
inline auto& UtxosetTotalBTCAmount = utxoset_total_btc_amount.Add({});
inline auto& UtxosetTx = utxoset_tx.Add({});
inline auto& UtxosetTxOutputs = utxoset_tx_outputs.Add({});
inline auto& TransactionsTotalCount = transactions_total_count.Add({});
inline auto& TransactionsTxRate = transactions_tx_rate.Add({});

/* ***************************** */

#endif // BITCOIN_PROMETHEUS_H
