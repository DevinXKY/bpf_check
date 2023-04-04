PHP_ARG_WITH(bpf_check, for bpf_check extension support,
[  --with-bpf_check             Enable bpf_check extension support])

if test "$PHP_BPF_CHECK" != "no"; then

    SEARCH_PATH="/usr/local /usr"
    SEARCH_FOR="/include/pcap.h"
    if test -r $PHP_BPF_CHECK/$SEARCH_FOR; then # path given as parameter
      PCAP_DIR=$PHP_BPF_CHECK
      AC_MSG_RESULT(from option: found in $PCAP_DIR)
    else # search default path list
      for i in $SEARCH_PATH ; do
        if test -r $i/$SEARCH_FOR; then
          PCAP_DIR=$i
          AC_MSG_RESULT(from default path: found in $i)
        fi
      done
    fi
    PHP_ADD_INCLUDE($PCAP_DIR/include)

    LIBNAME=pcap # you may want to change this
    LIBSYMBOL=pcap_compile_nopcap # you most likely want to change this
    PHP_CHECK_LIBRARY($LIBNAME, $LIBSYMBOL,
      AC_DEFINE(HAVE_PCAPLIB,1,[ ]),
    [
      AC_MSG_ERROR([wrong pcap library version or library not found])
    ],[
      -L$PCAP_DIR/lib -lm
    ])

    PHP_ADD_LIBRARY_WITH_PATH(pcap, $PCAP_DIR/lib, BPF_CHECK_SHARED_LIBADD)


  PHP_SUBST(BPF_CHECK_SHARED_LIBADD)
  PHP_NEW_EXTENSION(bpf_check, bpf_check.c, $ext_shared)
fi