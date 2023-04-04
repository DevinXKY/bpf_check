# bpf_check
php扩展 使用libpcap校验字符串是不是一个正确的bpf语句

```shell
phpize
./configure
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
