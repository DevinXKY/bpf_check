# bpf_check
使用libpcap库校验bpf语法是否正确的php扩展

```shell
phpize
./confure
make && make install
```

example
```php
<?php

if (!extension_loaded('bpf_check')) {
    echo 'skip';
}
$a = 'tcp port 80 and (((ip[2:2] - ((ip[0]&0xf)<<2>>2)) != 0)';
var_dump(bpf_check($a)); //(bool)true

```
