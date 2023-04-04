#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "bpf_check.h"

#define PHP_BPF_CHECK_EXTNAME "bpf_check"
#define PHP_BPF_CHECK_EXTVER  "0.1"

PHP_FUNCTION(bpf_check)
{
    char *filter = NULL;
    size_t filter_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s!", &filter, &filter_len) != SUCCESS) {
        RETURN_FALSE;
    }

    pcap_t *pcap_handle = pcap_open_dead(DLT_RAW, 65535);
    if (!pcap_handle) {
        RETURN_FALSE;
    }
    struct bpf_program bpf;
    int ret = pcap_compile(pcap_handle, &bpf, filter, 0, PCAP_NETMASK_UNKNOWN);
    pcap_close(pcap_handle);

    if (ret < 0) {
        RETURN_FALSE;
    }

    RETURN_TRUE;
}

PHP_FUNCTION(pcap_compile_version)
{
    const char *version = pcap_lib_version();
    RETURN_STRING(version);
}


static zend_function_entry bpf_check_functions[] = {
    PHP_FE(bpf_check, NULL)
    PHP_FE(pcap_compile_version, NULL)
    {NULL, NULL, NULL}
};

zend_module_entry bpf_check_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_BPF_CHECK_EXTNAME,
    bpf_check_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
#if ZEND_MODULE_API_NO >= 20010901
    PHP_BPF_CHECK_EXTVER,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_BPF_CHECK
ZEND_GET_MODULE(bpf_check)
#endif