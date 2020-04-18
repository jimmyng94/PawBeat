SOURCEFILES = Libraries/c-core/core/pubnub_pubsubapi.c Libraries/c-core/core/pubnub_coreapi.c Libraries/c-core/core/pubnub_coreapi_ex.c Libraries/c-core/core/pubnub_ccore_pubsub.c Libraries/c-core/core/pubnub_ccore.c Libraries/c-core/core/pubnub_netcore.c  Libraries/c-core/lib/sockets/pbpal_sockets.c Libraries/c-core/lib/sockets/pbpal_resolv_and_connect_sockets.c Libraries/c-core/lib/sockets/pbpal_handle_socket_error.c Libraries/c-core/core/pubnub_alloc_std.c Libraries/c-core/core/pubnub_assert_std.c Libraries/c-core/core/pubnub_generate_uuid.c Libraries/c-core/core/pubnub_blocking_io.c Libraries/c-core/posix/posix_socket_blocking_io.c Libraries/c-core/core/pubnub_timers.c Libraries/c-core/core/pubnub_json_parse.c Libraries/c-core/lib/md5/md5.c Libraries/c-core/lib/base64/pbbase64.c Libraries/c-core/lib/pb_strnlen_s.c Libraries/c-core/core/pubnub_helper.c Libraries/c-core/cpp/pubnub_version_posix.cpp Libraries/c-core/posix/pubnub_generate_uuid_posix.c Libraries/c-core/posix/pbpal_posix_blocking_io.c Libraries/c-core/core/pubnub_free_with_timeout_std.c Libraries/c-core/cpp/pubnub_subloop.cpp Libraries/c-core/posix/msstopwatch_monotonic_clock.c Libraries/c-core/posix/pbtimespec_elapsed_ms.c Libraries/c-core/core/pubnub_url_encode.c Libraries/c-core/core/pubnub_memory_block.c Libraries/c-core/posix/pb_sleep_ms.c Libraries/c-core/core/pubnub_log.h

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
SOURCEFILES += Libraries/c-core/core/pubnub_proxy.c Libraries/c-core/core/pubnub_proxy_core.c Libraries/c-core/core/pbhttp_digest.c Libraries/c-core/core/pbntlm_core.c Libraries/c-core/core/pbntlm_packer_std.c
endif

ifeq ($(USE_GZIP_COMPRESSION), 1)
SOURCEFILES += Libraries/c-core/lib/miniz/miniz_tdef.c Libraries/c-core/lib/miniz/miniz.c Libraries/c-core/lib/pbcrc32.c Libraries/c-core/core/pbgzip_compress.c
endif

ifeq ($(RECEIVE_GZIP_RESPONSE), 1)
SOURCEFILES += Libraries/c-core/lib/miniz/miniz_tinfl.c Libraries/c-core/core/pbgzip_decompress.c
endif

ifeq ($(USE_SUBSCRIBE_V2), 1)
SOURCEFILES += Libraries/c-core/core/pbcc_subscribe_v2.c Libraries/c-core/core/pubnub_subscribe_v2.c 
endif

ifeq ($(USE_ADVANCED_HISTORY), 1)
SOURCEFILES += Libraries/c-core/core/pbcc_advanced_history.c Libraries/c-core/core/pubnub_advanced_history.c
endif

ifeq ($(USE_OBJECTS_API), 1)
SOURCEFILES += Libraries/c-core/core/pbcc_objects_api.c Libraries/c-core/core/pubnub_objects_api.c
endif

ifeq ($(USE_ACTIONS_API), 1)
SOURCEFILES += Libraries/c-core/core/pbcc_actions_api.c Libraries/c-core/core/pubnub_actions_api.c
endif

ifeq ($(USE_AUTO_HEARTBEAT), 1)
SOURCEFILES += Libraries/c-core/core/pbauto_heartbeat.c Libraries/c-core/posix/pbauto_heartbeat_init_posix.c Libraries/c-core/lib/pbstr_remove_from_list.c
endif

OS := $(shell uname)
ifeq ($(OS),Darwin)
SOURCEFILES += Libraries/c-core/posix/monotonic_clock_get_time_darwin.c
LDLIBS=-lpthread
else
SOURCEFILES += Libraries/c-core/posix/monotonic_clock_get_time_posix.c
LDLIBS=-lrt -lpthread
endif

CFLAGS =-g -I Libraries/c-core -I Libraries/c-core/posix -I . -Wall -D PUBNUB_THREADSAFE -D PUBNUB_LOG_LEVEL=PUBNUB_LOG_LEVEL_WARNING -D PUBNUB_ONLY_PUBSUB_API=$(ONLY_PUBSUB_API) -D PUBNUB_PROXY_API=$(USE_PROXY) -D PUBNUB_USE_GZIP_COMPRESSION=$(USE_GZIP_COMPRESSION) -D PUBNUB_RECEIVE_GZIP_RESPONSE=$(RECEIVE_GZIP_RESPONSE) -D PUBNUB_USE_SUBSCRIBE_V2=$(USE_SUBSCRIBE_V2) -D PUBNUB_USE_OBJECTS_API=$(USE_OBJECTS_API) -D PUBNUB_USE_ACTIONS_API=$(USE_ACTIONS_API) -D PUBNUB_USE_AUTO_HEARTBEAT=$(USE_AUTO_HEARTBEAT)
# -g enables debugging, remove to get a smaller executable


all: cpp98

cpp98: pawpulseWebClient


##
# The socket poller module to use. You should use the `poll` poller, it
# doesn't have the weird restrictions of `select` poller. OTOH,
# select() on Windows is compatible w/BSD sockets select(), while
# WSAPoll() has some weird differences to poll().  The names are the
# same until the last `_`, then it's `poll` vs `select`.
SOCKET_POLLER_C=Libraries/c-core/lib/sockets/pbpal_ntf_callback_poller_poll.c

CALLBACK_INTF_SOURCEFILES= Libraries/c-core/posix/pubnub_ntf_callback_posix.c Libraries/c-core/posix/pubnub_get_native_socket.c Libraries/c-core/core/pubnub_timer_list.c Libraries/c-core/lib/sockets/pbpal_adns_sockets.c Libraries/c-core/lib/pubnub_dns_codec.c $(SOCKET_POLLER_C)  Libraries/c-core/core/pbpal_ntf_callback_queue.c Libraries/c-core/core/pbpal_ntf_callback_admin.c Libraries/c-core/core/pbpal_ntf_callback_handle_timer_list.c  Libraries/c-core/core/pubnub_callback_subscribe_loop.c

ifndef USE_DNS_SERVERS
USE_DNS_SERVERS = 1
endif

ifndef USE_IPV6
USE_IPV6 = 1
endif

ifeq ($(USE_DNS_SERVERS), 1)
CALLBACK_INTF_SOURCEFILES += Libraries/c-core/core/pubnub_dns_servers.c Libraries/c-core/posix/pubnub_dns_system_servers.c Libraries/c-core/lib/pubnub_parse_ipv4_addr.c
endif

ifeq ($(USE_IPV6), 1)
CALLBACK_INTF_SOURCEFILES += Libraries/c-core/lib/pubnub_parse_ipv6_addr.c
endif

CFLAGS_CALLBACK = -D PUBNUB_USE_IPV6=$(USE_IPV6) -D PUBNUB_SET_DNS_SERVERS=$(USE_DNS_SERVERS)

pawpulseWebClient: pawpulseWebClient.cpp $(SOURCEFILES) $(CALLBACK_INTF_SOURCEFILES) Libraries/c-core/cpp/pubnub_futres_posix.cpp
	$(CXX) -o $@ -D PUBNUB_CALLBACK_API $(CFLAGS) $(CFLAGS_CALLBACK) -D PUBNUB_THREADSAFE -x c++ pawpulseWebClient.cpp $(CALLBACK_INTF_SOURCEFILES) Libraries/c-core/cpp/pubnub_futres_posix.cpp $(SOURCEFILES) $(LDLIBS)

clean:
	rm  pawpulseWebClient *.dSYM
