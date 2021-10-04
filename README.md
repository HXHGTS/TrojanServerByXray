# TrojanServerByXray

## 警告⚠：此技术仅限用于个人搭建游戏加速器使用！！！若用于其他违法目的，后果自负！！！

利用Xray搭建trojan服务器

KVM/XEN机器执行(CentOS7):

`yum install -y gcc wget && wget https://raw.githubusercontent.com/HXHGTS/TrojanServerByXray/main/trojan.c -O trojan.c && chmod +x trojan.c && gcc -o xray trojan.c && ./xray`

OVZ机器执行(CentOS7):

`yum install -y gcc wget && wget https://raw.githubusercontent.com/HXHGTS/TrojanServerByXray/main/trojan_no_kernel_update.c -O trojan.c && chmod +x trojan.c && gcc -o xray trojan.c && ./xray`

KVM/XEN/LXC/OVZ机器执行(CentOS8):

`yum install -y gcc wget && wget https://raw.githubusercontent.com/HXHGTS/TrojanServerByXray/main/trojan_centos8.c -O trojan.c && chmod +x trojan.c && gcc -o xray trojan.c && ./xray`

KVM/XEN机器执行(Debian9/10):

`apt update && apt install -y build-essential wget && wget https://raw.githubusercontent.com/HXHGTS/TrojanServerByXray/main/trojan_debian10.c -O trojan.c && chmod +x trojan.c && gcc -o xray trojan.c && ./xray`


第一次点击安装后会自动升级系统内核并触发重启，重启后输入

`./xray`

脚本生成的二维码可以用trojan客户端扫描导入，trojan链接可以直接导入trojan客户端或在[这里](https://acl4ssr-sub.github.io/)生成Clash链接以导入Clash

### 安装前准备：

1.一个域名，与服务器ip做好dns解析

2.该域名必须提前申请SSL证书用于加密（后续考虑加入自动申请证书），将证书(*.cer/*.crt/*.pem)文件命名为1.pem，将私钥(*.key/*.pem)文件命名为2.pem，放在/root目录下(SSL证书申请:[腾讯云](https://console.cloud.tencent.com/ssl) [阿里云](https://common-buy.aliyun.com/?spm=5176.b5912525.0.0.3c07GExwGExwfv&commodityCode=cas) [FreeSSL](https://freessl.cn/))

3.脚本仅支持CentOS7/CentOS8/Debian9/Debian10系统

4.脚本执行需要root权限登录系统，AWS等特殊机型打开root权限方法[看这里](https://hxhgts.github.io/AWSECSRoot/)

5.请在服务器后台防火墙放行tcp2053(knetd)端口
