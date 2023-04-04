#ifndef PHP_BPF_CHECK_H
#define PHP_BPF_CHECK_H

#include <pcap/pcap.h>
#include "php.h"
#ifdef ZTS
#include "TSRM.h"
#endif

extern zend_module_entry bpf_check_module_entry;
#define phpext_bpf_check_ptr &bpf_check_module_entry

#endif /* PHP_BPF_CHECK_H */