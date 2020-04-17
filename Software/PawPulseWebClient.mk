SOURCEFILES = ../pubnub/core/pubnub_pubsubapi.c ../pubnub/core/pubnub_coreapi.c ../pubnub/core/pubnub_coreapi_ex.c ../pubnub/core/pubnub_ccore_pubsub.c ../pubnub/core/pubnub_ccore.c ../pubnub/core/pubnub_netcore.c  ../pubnub/lib/sockets/pbpal_sockets.c ../pubnub/lib/sockets/pbpal_resolv_and_connect_sockets.c ../pubnub/lib/sockets/pbpal_handle_socket_error.c ../pubnub/core/pubnub_alloc_std.c ../pubnub/core/pubnub_assert_std.c ../pubnub/core/pubnub_generate_uuid.c ../pubnub/core/pubnub_blocking_io.c ../pubnub/posix/posix_socket_blocking_io.c ../pubnub/core/pubnub_timers.c ../pubnub/core/pubnub_json_parse.c ../pubnub/lib/md5/md5.c ../pubnub/lib/base64/pbbase64.c ../pubnub/lib/pb_strnlen_s.c ../pubnub/core/pubnub_helper.c ../pubnub/cpp/pubnub_version_posix.cpp ../pubnub/posix/pubnub_generate_uuid_posix.c ../pubnub/posix/pbpal_posix_blocking_io.c ../pubnub/core/pubnub_free_with_timeout_std.c ../pubnub/cpp/pubnub_subloop.cpp ../pubnub/posix/msstopwatch_monotonic_clock.c ../pubnub/posix/pbtimespec_elapsed_ms.c ../pubnub/core/pubnub_url_encode.c ../pubnub/core/pubnub_memory_block.c ../pubnub/posix/pb_sleep_ms.c ../pubnub/core/pubnub_log.h

ifndef ONLY_PUBSUB_API
ONLY_PUBSUB_API = 0
endif

ifndef USE_PROXY
USE_PROXY = 1
endif

ifndef USE_GZIP_COMPRESSION
USE_GZIP_COMPRESSION = 1
endif

ifndef RECEIVE_GZIP_RESPONSE
RECEIVE_GZIP_RESPONSE = 1
endif

ifndef USE_SUBSCRIBE_V2
USE_SUBSCRIBE_V2 = 1
endif

ifndef USE_ADVANCED_HISTORY
USE_ADVANCED_HISTORY = 1
endif

ifndef USE_OBJECTS_API
USE_OBJECTS_API = 1
endif

ifndef USE_ACTIONS_API
USE_ACTIONS_API = 1
endif

ifndef USE_AUTO_HEARTBEAT
USE_AUTO_HEARTBEAT = 1
endif

ifeq ($(USE_PROXY), 1)
SOURCEFILES += ../pubnub/core/pubnub_proxy.c ../pubnub/core/pubnub_proxy_core.c ../pubnub/core/pbhttp_digest.c ../pubnub/core/pbntlm_core.c ../pubnub/core/pbntlm_packer_std.c
endif

ifeq ($(USE_GZIP_COMPRESSION), 1)
SOURCEFILES += ../pubnub/lib/miniz/miniz_tdef.c ../pubnub/lib/miniz/miniz.c ../pubnub/lib/pbcrc32.c ../pubnub/core/pbgzip_compress.c
endif

ifeq ($(RECEIVE_GZIP_RESPONSE), 1)
SOURCEFILES += ../pubnub/lib/miniz/miniz_tinfl.c ../pubnub/core/pbgzip_decompress.c
endif

ifeq ($(USE_SUBSCRIBE_V2), 1)
SOURCEFILES += ../pubnub/core/pbcc_subscribe_v2.c ../pubnub/core/pubnub_subscribe_v2.c 
endif

ifeq ($(USE_ADVANCED_HISTORY), 1)
SOURCEFILES += ../pubnub/core/pbcc_advanced_history.c ../pubnub/core/pubnub_advanced_history.c
endif

ifeq ($(USE_OBJECTS_API), 1)
SOURCEFILES += ../pubnub/core/pbcc_objects_api.c ../pubnub/core/pubnub_objects_api.c
endif

ifeq ($(USE_ACTIONS_API), 1)
SOURCEFILES += ../pubnub/core/pbcc_actions_api.c ../pubnub/core/pubnub_actions_api.c
endif

ifeq ($(USE_AUTO_HEARTBEAT), 1)
SOURCEFILES += ../pubnub/core/pbauto_heartbeat.c ../pubnub/posix/pbauto_heartbeat_init_posix.c ../pubnub/lib/pbstr_remove_from_list.c
endif

OS := $(shell uname)
ifeq ($(OS),Darwin)
SOURCEFILES += ../pubnub/posix/monotonic_clock_get_time_darwin.c
LDLIBS=-lpthread
else
SOURCEFILES += ../pubnub/posix/monotonic_clock_get_time_posix.c
LDLIBS=-lrt -lpthread
endif

CFLAGS =-g -I ../pubnub -I ../pubnub/posix -I . -Wall -D PUBNUB_THREADSAFE -D PUBNUB_LOG_LEVEL=PUBNUB_LOG_LEVEL_WARNING -D PUBNUB_ONLY_PUBSUB_API=$(ONLY_PUBSUB_API) -D PUBNUB_PROXY_API=$(USE_PROXY) -D PUBNUB_USE_GZIP_COMPRESSION=$(USE_GZIP_COMPRESSION) -D PUBNUB_RECEIVE_GZIP_RESPONSE=$(RECEIVE_GZIP_RESPONSE) -D PUBNUB_USE_SUBSCRIBE_V2=$(USE_SUBSCRIBE_V2) -D PUBNUB_USE_OBJECTS_API=$(USE_OBJECTS_API) -D PUBNUB_USE_ACTIONS_API=$(USE_ACTIONS_API) -D PUBNUB_USE_AUTO_HEARTBEAT=$(USE_AUTO_HEARTBEAT)
# -g enables debugging, remove to get a smaller executable


all: cpp98

cpp98: sendDataClient


##
# The socket poller module to use. You should use the `poll` poller, it
# doesn't have the weird restrictions of `select` poller. OTOH,
# select() on Windows is compatible w/BSD sockets select(), while
# WSAPoll() has some weird differences to poll().  The names are the
# same until the last `_`, then it's `poll` vs `select`.
SOCKET_POLLER_C=../pubnub/lib/sockets/pbpal_ntf_callback_poller_poll.c

CALLBACK_INTF_SOURCEFILES= ../pubnub/posix/pubnub_ntf_callback_posix.c ../pubnub/posix/pubnub_get_native_socket.c ../pubnub/core/pubnub_timer_list.c ../pubnub/lib/sockets/pbpal_adns_sockets.c ../pubnub/lib/pubnub_dns_codec.c $(SOCKET_POLLER_C)  ../pubnub/core/pbpal_ntf_callback_queue.c ../pubnub/core/pbpal_ntf_callback_admin.c ../pubnub/core/pbpal_ntf_callback_handle_timer_list.c  ../pubnub/core/pubnub_callback_subscribe_loop.c

ifndef USE_DNS_SERVERS
USE_DNS_SERVERS = 1
endif

ifndef USE_IPV6
USE_IPV6 = 1
endif

ifeq ($(USE_DNS_SERVERS), 1)
CALLBACK_INTF_SOURCEFILES += ../pubnub/core/pubnub_dns_servers.c ../pubnub/posix/pubnub_dns_system_servers.c ../pubnub/lib/pubnub_parse_ipv4_addr.c
endif

ifeq ($(USE_IPV6), 1)
CALLBACK_INTF_SOURCEFILES += ../pubnub/lib/pubnub_parse_ipv6_addr.c
endif

CFLAGS_CALLBACK = -D PUBNUB_USE_IPV6=$(USE_IPV6) -D PUBNUB_SET_DNS_SERVERS=$(USE_DNS_SERVERS)

sendDataClient: sendDataClient.cpp $(SOURCEFILES) $(CALLBACK_INTF_SOURCEFILES) ../pubnub/cpp/pubnub_futres_posix.cpp
	$(CXX) -o $@ -D PUBNUB_CALLBACK_API $(CFLAGS) $(CFLAGS_CALLBACK) -D PUBNUB_THREADSAFE -x c++ sendDataClient.cpp $(CALLBACK_INTF_SOURCEFILES) ../pubnub/cpp/pubnub_futres_posix.cpp $(SOURCEFILES) $(LDLIBS)

clean:
	rm  sendDataClient *.dSYM
