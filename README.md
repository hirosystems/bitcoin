Bitcoin Core + Prometheus Metrics

What is This?
----------------
Modelled after [Statoshi](https://github.com/jlopp/statoshi), this is similar in scope but uses Prometheus rather than statsd.

Objective is to protect Bitcoin by bringing transparency to the activity
occurring on the node network. By making this data available, Bitcoin developers can
learn more about node performance, gain operational insight about the network, and
the community can be informed about attacks and aberrant behavior in a timely fashion.

Prometheus Library Used: [prometheus-cpp](https://github.com/jupp0r/prometheus-cpp)

Config:
----------------
Enabled by default, to disable: `-promserver 0`
- `-promserverbind` will bind the server to an `<ip>[:port]` similar to how `-rpcbind` works.

Example config options to bind to all interfaces on port `9153`:
```
promserver=0
promserverbind=0.0.0.0:9153
```

Prerequisites:
----------------
1. DB4
2. [prometheus-cpp](https://github.com/jupp0r/prometheus-cpp)
- For MacOS, this can be accomplished with brew:
```bash
$ brew install berkeley-db@4
$ brew install prometheus-cpp
```

**db4** source install:
```bash
$ wget https://download.oracle.com/berkeley-db/db-4.8.30.NC.tar.gz -O /tmp/db-4.8.30.NC.tar.gz
$ tar -xzf /tmp/db-4.8.30.NC.tar.gz -C /tmp/
$ sed s/__atomic_compare_exchange/__atomic_compare_exchange_db/g -i /tmp/db-4.8.30.NC/dbinc/atomic.h
$ cd /tmp/db-4.8.30.NC/build_unix
$ ../dist/configure --enable-cxx --disable-shared --with-pic --prefix=/usr
$ make -j4
$ sudo make install
```

**prometheus-cpp** source install:
```bash
$ git clone https://github.com/jupp0r/prometheus-cpp prometheus-cpp
$ cd prometheus-cpp
$ git submodule init
$ git submodule update
$ mkdir _build
$ cd _build
$ cmake -DCMAKE_INSTALL_PREFIX=/usr .. -DBUILD_SHARED_LIBS=ON
$ make -j 4
$ sudo make install
```

Building Docker Image
----------------
An alpine based [Dockerfile](./docker/Dockerfile) is provided in the `./docker` directory with a [build script](./docker/docker-build.sh) to create a standalone image.
```bash
$ docker build --progress plain  -f docker/Dockerfile -t bitcoin:prometheus .
```

Building Bitcoin:
----------------
```bash
$ ./autogen.sh
```

`$PROM_CPPFLAGS` used in the configure options are dependent on where you install the prerequisite [prometheus-cpp](https://github.com/jupp0r/prometheus-cpp) header files. Without this variable set, the build will fail.
- For MacOS with brew, this will be similar to: `export PROM_CPPFLAGS="-I/usr/local/opt/prometheus-cpp/include"`
- For Linux with a `/usr` prefix: `export PROM_CPPFLAGS="-I/usr/include/prometheus"`

```bash
$ ./configure \
    --with-boost \
    --with-boost-thread \
    --enable-util-cli $OPTS \
    --disable-gui-tests \
    --enable-static \
    --disable-tests \
    --disable-bench \
    --without-miniupnpc \
    --disable-shared \
    --with-pic \
    --enable-cxx \
    CPPFLAGS="${PROM_CPPFLAGS} -static-libstdc++" \
    LDFLAGS="-lprometheus-cpp-pull -lprometheus-cpp-push -lprometheus-cpp-core -lcurl -lz" \
```

```bash
$ make STATIC=1
$ sudo make install
```

Sample metrics output via curl
----------------
`curl localhost:9153/metrics`:
```
# HELP btc_message_sent Count of Messages Sent
# TYPE btc_message_sent counter
btc_message_sent{name="feefilter"} 2.00000000000000000
btc_message_sent{name="ping"} 2.00000000000000000
btc_message_sent{name="sendcmpct"} 4.00000000000000000
btc_message_sent{name="sendaddrv2"} 1.00000000000000000
btc_message_sent{name="getaddr"} 2.00000000000000000
btc_message_sent{name="verack"} 2.00000000000000000
btc_message_sent{name="sendheaders"} 2.00000000000000000
btc_message_sent{name="wtxidrelay"} 1.00000000000000000
btc_message_sent{name="version"} 3.00000000000000000
# HELP btc_misbehavior_banned Count of Banned Peers
# TYPE btc_misbehavior_banned counter
btc_misbehavior_banned 0.00000000000000000
# HELP btc_transactions_accepted Count of Transactions Accepted
# TYPE btc_transactions_accepted counter
btc_transactions_accepted 0.00000000000000000
# HELP btc_transactions_fees Current Transaction Fees
# TYPE btc_transactions_fees counter
btc_transactions_fees 0.00000000000000000
# HELP btc_transactions_input_value Current Transaction Input Value
# TYPE btc_transactions_input_value counter
btc_transactions_input_value 0.00000000000000000
# HELP btc_transactions_inputs Current Transaction Input
# TYPE btc_transactions_inputs counter
btc_transactions_inputs 0.00000000000000000
# HELP btc_transactions_output_value Current Transaction Output Value
# TYPE btc_transactions_output_value counter
btc_transactions_output_value 0.00000000000000000
# HELP btc_transactions_outputs Current Transaction Output
# TYPE btc_transactions_outputs counter
btc_transactions_outputs 0.00000000000000000
# HELP btc_transactions_sig_ops Current Transaction SigOps
# TYPE btc_transactions_sig_ops counter
btc_transactions_sig_ops 0.00000000000000000
# HELP btc_transactions_size_bytes Transaction Size in Bytes
# TYPE btc_transactions_size_bytes counter
btc_transactions_size_bytes 0.00000000000000000
# HELP btc_warnings_invalid_block Count of Invalid Block Warning
# TYPE btc_warnings_invalid_block counter
btc_warnings_invalid_block 0.00000000000000000
# HELP btc_bandwidth_message_bytes_received Bandwidth Received Messages in bytes
# TYPE btc_bandwidth_message_bytes_received counter
btc_bandwidth_message_bytes_received{name="pong"} 32.00000000000000000
btc_bandwidth_message_bytes_received{name="getheaders"} 1085.00000000000000000
btc_bandwidth_message_bytes_received{name="feefilter"} 32.00000000000000000
btc_bandwidth_message_bytes_received{name="version"} 253.00000000000000000
btc_bandwidth_message_bytes_received{name="ping"} 32.00000000000000000
btc_bandwidth_message_bytes_received{name="sendcmpct"} 66.00000000000000000
btc_bandwidth_message_bytes_received{name="wtxidrelay"} 24.00000000000000000
btc_bandwidth_message_bytes_received{name="verack"} 48.00000000000000000
btc_bandwidth_message_bytes_received{name="sendaddrv2"} 24.00000000000000000
btc_bandwidth_message_bytes_received{name="addr"} 55.00000000000000000
btc_bandwidth_message_bytes_received{name="sendheaders"} 24.00000000000000000
btc_bandwidth_message_bytes_received 0.00000000000000000
# HELP btc_bandwidth_message_bytes_sent Bandwidth Sent Messages in bytes
# TYPE btc_bandwidth_message_bytes_sent counter
btc_bandwidth_message_bytes_sent{name="feefilter"} 64.00000000000000000
btc_bandwidth_message_bytes_sent{name="ping"} 64.00000000000000000
btc_bandwidth_message_bytes_sent{name="sendcmpct"} 132.00000000000000000
btc_bandwidth_message_bytes_sent{name="getaddr"} 48.00000000000000000
btc_bandwidth_message_bytes_sent{name="sendaddrv2"} 24.00000000000000000
btc_bandwidth_message_bytes_sent{name="version"} 381.00000000000000000
btc_bandwidth_message_bytes_sent{name="verack"} 48.00000000000000000
btc_bandwidth_message_bytes_sent{name="sendheaders"} 48.00000000000000000
btc_bandwidth_message_bytes_sent{name="wtxidrelay"} 24.00000000000000000
btc_bandwidth_message_bytes_sent 0.00000000000000000
# HELP time_running_seconds_total How many seconds is this server running?
# TYPE time_running_seconds_total counter
time_running_seconds_total{label="value"} 24.00000000000000000
# HELP btc_accept_to_memory_pool_ms Time to accept to memory pool in ms
# TYPE btc_accept_to_memory_pool_ms gauge
btc_accept_to_memory_pool_ms 0.00000000000000000
# HELP btc_activate_best_chain_ms Time to activate best chain in ms
# TYPE btc_activate_best_chain_ms gauge
btc_activate_best_chain_ms 0.00000000000000000
# HELP btc_activate_block_ms Time to activate block in ms
# TYPE btc_activate_block_ms gauge
btc_activate_block_ms 0.00000000000000000
# HELP btc_bandwidth_bytes_received Bandwidth Received in bytes
# TYPE btc_bandwidth_bytes_received gauge
btc_bandwidth_bytes_received 32.00000000000000000
# HELP btc_badwidth_bytes_sent Bandwidth Received in bytes
# TYPE btc_badwidth_bytes_sent gauge
btc_badwidth_bytes_sent 32.00000000000000000
# HELP btc_block_height Block Height
# TYPE btc_block_height gauge
btc_block_height 1939893.00000000000000000
# HELP btc_block_num_transations Count of Transactions
# TYPE btc_block_num_transations gauge
btc_block_num_transations 46.00000000000000000
# HELP btc_block_sigops Count of SigOps
# TYPE btc_block_sigops gauge
btc_block_sigops 20.00000000000000000
# HELP btc_block_current_size_bytes Current block size in bytes
# TYPE btc_block_current_size_bytes gauge
btc_block_current_size_bytes 9480.00000000000000000
# HELP btc_block_current_size_witness_bytes Current witness block size in bytes
# TYPE btc_block_current_size_witness_bytes gauge
btc_block_current_size_witness_bytes 17990.00000000000000000
# HELP btc_block_version Current Block Version
# TYPE btc_block_version gauge
btc_block_version 536928256.00000000000000000
# HELP btc_block_weight Current Block Weight
# TYPE btc_block_weight gauge
btc_block_weight 46430.00000000000000000
# HELP btc_check_block_us Time to check block in us
# TYPE btc_check_block_us gauge
btc_check_block_us 85.00000000000000000
# HELP btc_check_inputs_ms Time to check inputs in ms
# TYPE btc_check_inputs_ms gauge
btc_check_inputs_ms 0.00000000000000000
# HELP btc_check_transaction_us Time to check transactions in us
# TYPE btc_check_transaction_us gauge
btc_check_transaction_us 0.00000000000000000
# HELP btc_connect_block_ms Time to connect block in ms
# TYPE btc_connect_block_ms gauge
btc_connect_block_ms 2.00000000000000000
# HELP btc_connect_tip_ms Time to connect tip in ms
# TYPE btc_connect_tip_ms gauge
btc_connect_tip_ms 1303.00000000000000000
# HELP btc_disconnect_block_ms time to disconnect block in ms
# TYPE btc_disconnect_block_ms gauge
btc_disconnect_block_ms 24.00000000000000000
# HELP btc_fee_name Fee Estimage
# TYPE btc_fee_name gauge
btc_fee_name 1000.00000000000000000
# HELP btc_message_received_inv_block Count of inv block messages
# TYPE btc_message_received_inv_block gauge
btc_message_received_inv_block 0.00000000000000000
# HELP btc_message_received_inv_tx Count of inv tx messages
# TYPE btc_message_received_inv_tx gauge
btc_message_received_inv_tx 0.00000000000000000
# HELP btc_misbehavior_amount Misbehavior Amount
# TYPE btc_misbehavior_amount gauge
btc_misbehavior_amount 0.00000000000000000
# HELP btc_network_difficulty Current Network Difficulty
# TYPE btc_network_difficulty gauge
btc_network_difficulty 0.00000000000000000
# HELP btc_network_exahashes_per_second Current network exahashes per second
# TYPE btc_network_exahashes_per_second gauge
btc_network_exahashes_per_second 0.00000000000000000
# HELP btc_peers_connect Current peers connected
# TYPE btc_peers_connect gauge
btc_peers_connect 4.00000000000000000
# HELP btc_peers_disconnect Current peers disconnected
# TYPE btc_peers_disconnect gauge
btc_peers_disconnect 1.00000000000000000
# HELP btc_peers_full_node_connections Current Peers connected as full node
# TYPE btc_peers_full_node_connections gauge
btc_peers_full_node_connections 2.00000000000000000
# HELP btc_peers_inbound_connections Current inbound connections
# TYPE btc_peers_inbound_connections gauge
btc_peers_inbound_connections 0.00000000000000000
# HELP btc_peers_ipv4_connections Current IPv4 connections
# TYPE btc_peers_ipv4_connections gauge
btc_peers_ipv4_connections 2.00000000000000000
# HELP btc_peers_ipv6_connections Current IPv6 connections
# TYPE btc_peers_ipv6_connections gauge
btc_peers_ipv6_connections 0.00000000000000000
# HELP btc_peers_known_addresses Current known peer addresses
# TYPE btc_peers_known_addresses gauge
btc_peers_known_addresses 0.00000000000000000
# HELP btc_peers_outbound_connections Current outputbound peer connections
# TYPE btc_peers_outbound_connections gauge
btc_peers_outbound_connections 2.00000000000000000
# HELP btc_peers_ping_us Current peer ping time in us
# TYPE btc_peers_ping_us gauge
btc_peers_ping_us 0.00000000000000000
# HELP btc_peers_spv_node_connections Current spv connections
# TYPE btc_peers_spv_node_connections gauge
btc_peers_spv_node_connections 0.00000000000000000
# HELP btc_peers_tor_connections Current TOR connections
# TYPE btc_peers_tor_connections gauge
btc_peers_tor_connections 0.00000000000000000
# HELP btc_peers_total_connections Current total peer connections
# TYPE btc_peers_total_connections gauge
btc_peers_total_connections 2.00000000000000000
# HELP btc_transactions_duplicate Current duplicate transactions
# TYPE btc_transactions_duplicate gauge
btc_transactions_duplicate 0.00000000000000000
# HELP btc_transactions_mempool_memory_usage_bytes Current tx mempoool memory usage in bytes
# TYPE btc_transactions_mempool_memory_usage_bytes gauge
btc_transactions_mempool_memory_usage_bytes 0.00000000000000000
# HELP btc_transactions_mempool_min_free_per_kb Current tx mempoool memory min free in kb
# TYPE btc_transactions_mempool_min_free_per_kb gauge
btc_transactions_mempool_min_free_per_kb 0.00000000000000000
# HELP btc_transactions_mempool_total_transactions Current Transactions in mempool
# TYPE btc_transactions_mempool_total_transactions gauge
btc_transactions_mempool_total_transactions 0.00000000000000000
# HELP btc_transactions_mempool_total_tx_bytes Current transactions in mempool in bytes
# TYPE btc_transactions_mempool_total_tx_bytes gauge
btc_transactions_mempool_total_tx_bytes 0.00000000000000000
# HELP btc_transactions_orphans Current oprhaned transactions
# TYPE btc_transactions_orphans gauge
btc_transactions_orphans 0.00000000000000000
# HELP btc_transactions_orphans_add Current added orphaned transactions
# TYPE btc_transactions_orphans_add gauge
btc_transactions_orphans_add 0.00000000000000000
# HELP btc_transactions_orphans_remove Current removed orphaned transactions
# TYPE btc_transactions_orphans_remove gauge
btc_transactions_orphans_remove 0.00000000000000000
# HELP btc_transactions_tx_cache_size Current transaction tx cache size
# TYPE btc_transactions_tx_cache_size gauge
btc_transactions_tx_cache_size 382.00000000000000000
# HELP btc_transactions_tx_in_memory_pool Current transactions in mempool
# TYPE btc_transactions_tx_in_memory_pool gauge
btc_transactions_tx_in_memory_pool 0.00000000000000000
# HELP btc_utxoset_block_height Current utxoset block height
# TYPE btc_utxoset_block_height gauge
btc_utxoset_block_height 0.00000000000000000
# HELP btc_utxoset_db_size_bytes Current utxoset db size in bytes
# TYPE btc_utxoset_db_size_bytes gauge
btc_utxoset_db_size_bytes 0.00000000000000000
# HELP btc_utxoset_total_btc_amount Current utxoset in btc
# TYPE btc_utxoset_total_btc_amount gauge
btc_utxoset_total_btc_amount 0.00000000000000000
# HELP btc_utxoset_tx Current utxoset tx
# TYPE btc_utxoset_tx gauge
btc_utxoset_tx 0.00000000000000000
# HELP btc_utxoset_tx_outputs Current utxoset tx outputs
# TYPE btc_utxoset_tx_outputs gauge
btc_utxoset_tx_outputs 0.00000000000000000
# HELP btc_transactions_total_count Current total transactions
# TYPE btc_transactions_total_count gauge
```

License
-------

This is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see http://opensource.org/licenses/MIT.
