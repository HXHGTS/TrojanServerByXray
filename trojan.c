#include <stdio.h>
#include <stdlib.h>


FILE* config,* cer;
char passwd[30],sni[30];
int mode;

int main(){
Menu:UI();
    system("clear");
    if (mode == 1) {
        install_xray();
        goto Menu;
    }
    else if (mode == 2) {
        system("systemctl stop xray");
        system("systemctl start xray");
        printf("正在检测xray运行状态，以下输出不为空则运行正常！\n");
        printf("---------------以下输出为绿色则xray运行正常-----------------\n");
        system("systemctl status xray -l");
        system("ss -lp | grep xray");
        printf("\n--------------------------------------------------------\n");
        goto Menu;
    }
    else if (mode == 3) {
        printf("xray二维码:\n\n");
        system("qrencode -t ansiutf8 < /usr/local/etc/xray/trojan.txt");
        printf("\n\n");
        printf("trojan链接:\n\n");
        system("cat /usr/local/etc/xray/trojan.txt");
        printf("\n");
        goto Menu;
    }
    else if (mode == 4) {
        system("vi /usr/local/etc/xray/config.json");
        system("systemctl restart xray");
        printf("正在检测xray运行状态，以下输出不为空则运行正常！\n");
        printf("---------------以下输出为绿色则xray运行正常-----------------\n");
        system("systemctl status xray -l");
        system("ss -lp | grep xray");
        printf("\n--------------------------------------------------------\n");
        goto Menu;
    }
    else if (mode == 5) {
        if (fopen("/root/1.pem", "r") == NULL || fopen("/root/2.pem", "r") == NULL) {
            printf("检测到证书与私钥文件未按照规定方式放置于根目录，强制退出！\n");
            exit(0);
        }
        printf("请输入已绑定此服务器ip的新域名:");
        scanf("%s", sni);
        config = fopen("/usr/local/etc/sni.conf", "w");
        fprintf(config, "%s", sni);
        fclose(config);
        config = fopen("/usr/local/etc/xray/passwd.conf", "r");
        fscanf(config, "%s",passwd);
        fclose(config);
        printf("正在复制SSL证书与私钥. . .\n");
        system("cp -rf /root/1.pem /usr/local/etc/xray/certificate.crt");
        system("cp -rf /root/2.pem /usr/local/etc/xray/private.key"); 
        QRCodeGen();
        printf("正在检测xray运行状态，以下输出不为空则运行正常！\n");
        printf("---------------以下输出为绿色则xray运行正常-----------------\n");
        system("systemctl status xray -l");
        system("ss -lp | grep xray");
        printf("\n--------------------------------------------------------\n");
        printf("xray部署完成！\n");
        printf("xray二维码:\n\n");
        system("qrencode -t ansiutf8 < /usr/local/etc/xray/trojan.txt");
        printf("\n\n");
        printf("trojan链接:\n\n");
        system("cat /usr/local/etc/xray/trojan.txt");
        goto Menu;
    }
    else if (mode == 6) {
        printf("正在更新xray主程序. . .\n");
        system("systemctl stop xray");
        system("wget https://raw.githubusercontent.com/XTLS/Xray-install/master/install-release.sh -O install-release.sh");
        system("bash install-release.sh");
        system("rm -f install-release.sh");
        system("systemctl start xray");
        printf("xray主程序更新完成！\n");
        printf("正在检测xray运行状态，以下输出不为空则运行正常！\n");
        printf("---------------以下输出为绿色则xray运行正常-----------------\n");
        system("systemctl status xray -l");
        system("ss -lp | grep xray");
        printf("\n--------------------------------------------------------\n");
        goto Menu;
    }
    else if (mode == 7) {
        system("systemctl stop xray");
        system("systemctl disable xray");
        system("systemctl status xray");
        goto Menu;
    }
    else {
        exit(0);
    }
    return 0;
}

int UI() {
    printf("-----------------------------------------------------------\n");
    printf("----------------------xray安装工具-----------------------\n");
    printf("-----------------------------------------------------------\n");
    printf("安装前或需要更新SSL证书，请将证书(*.cer/*.crt/*.pem)与私钥(*.key/*.pem)分别命名为1.pem与2.pem，上传至服务器/root目录\n");
    printf("-----------------------------------------------------------\n");
    printf("----------------------当前Kernel版本-----------------------\n");
    system("uname -sr");
    printf("-----------------------------------------------------------\n");
    printf("1.安装xray\n2.运行xray\n3.显示配置\n4.修改xray配置\n5.更新域名与SSL证书\n6.更新xray\n7.关闭xray\n0.退出\n");
    printf("-----------------------------------------------------------\n");
    printf("请输入:");
    scanf("%d", &mode);
    return 0;
}

int install_xray() {
    KernelUpdate(); 
    config = fopen("/usr/local/etc/sni.conf", "r");
    fscanf(config, "%s", sni);
    fclose(config);
    system("setenforce 0");
    system("yum install -y pwgen bind-utils qrencode");
    printf("正在运行xray安装脚本. . .\n");
    system("wget https://cdn.jsdelivr.net/gh/XTLS/Xray-install/install-release.sh -O install-release.sh");
    system("chmod +x install-release.sh");
    system("bash install-release.sh");
    system("sleep 3");
    system("rm -rf install-release.sh");
    system("rm -rf TCPO.sh");
    printf("正在复制SSL证书与私钥. . .\n");
    system("cp -rf /root/1.pem /usr/local/etc/xray/certificate.crt");
    system("cp -rf /root/2.pem /usr/local/etc/xray/private.key");
    printf("正在生成配置文件. . .\n");
    system("curl https://raw.githubusercontent.com/HXHGTS/TrojanServerByXray/main/config.json.1 > /usr/local/etc/xray/config.json");
    printf("正在生成强密码. . .\n");
    system("pwgen -s 28 1 > /usr/local/etc/xray/passwd.conf");
    config = fopen("/usr/local/etc/xray/passwd.conf", "r");
    fscanf(config, "%s",passwd);
    fclose(config);
    config = fopen("/usr/local/etc/xray/config.json", "a");
    fprintf(config, "                        \"password\":\"%s\"\n", passwd);
    fclose(config);
    system("curl https://raw.githubusercontent.com/HXHGTS/TrojanServerByXray/main/config.json.2 >> /usr/local/etc/xray/config.json");
    printf("正在启动xray并将xray写入开机引导项. . .\n");
    system("systemctl stop xray");
    system("systemctl enable xray && systemctl start xray");
    QRCodeGen();
    printf("正在检测xray运行状态，以下输出不为空则运行正常！\n");
    printf("---------------以下输出为绿色则xray运行正常-----------------\n");
    system("systemctl status xray -l");
    system("ss -lp | grep xray");
    printf("\n--------------------------------------------------------\n");
    printf("xray部署完成！\n");
    printf("xray二维码:\n\n");
    system("qrencode -t ansiutf8 < /usr/local/etc/xray/trojan.txt");
    printf("\n\n");
    printf("trojan链接:\n\n");
    system("cat /usr/local/etc/xray/trojan.txt");
    return 0;
}

int QRCodeGen() {
    config = fopen("/usr/local/etc/xray/trojan.txt", "w");
    fprintf(config, "trojan://%s@%s:2053#%s\n",passwd,sni,sni);
    fclose(config);
    return 0;
}

int KernelUpdate() {
    if ((fopen("KernelUpdate.sh", "r")) == NULL) {
        if (fopen("/root/1.pem", "r") == NULL || fopen("/root/2.pem", "r") == NULL) {
        printf("检测到证书与私钥文件未按照规定方式放置于根目录，强制退出！\n");
        exit(0);
    }
        printf("请输入已绑定此服务器ip的域名:");
        scanf("%s", sni);
        config = fopen("/usr/local/etc/sni.conf", "w");
        fprintf(config, "%s", sni);
        fclose(config);
        printf("正在升级新内核. . .\n");
        system("wget https://cdn.jsdelivr.net/gh/HXHGTS/TCPOptimization/KernelUpdate.sh -O KernelUpdate.sh");
        system("chmod +x KernelUpdate.sh");
        printf("正在升级，将自动触发重启以应用配置. . .\n");
        system("bash KernelUpdate.sh");
    }
    else {
        system("curl -sSL https://cdn.jsdelivr.net/gh/HXHGTS/TCPOptimization/TCPO.sh | sh");
    }
    return 0;
}
