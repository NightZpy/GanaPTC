#include <oPen/oPenCURL.cpp>
#include <oPen/oPenXML.cpp>
#include <QApplication>
#include "dialog.h"
#include "ui_dialog.h"

int registerVB(char user[12], char pwd[12], char parmpmail[32], char parmMail[32], char referer[12])
{
    //Se ha registrado correctamente

    if(strlen(user)<3)
    {
        cout << "[!] usuario invalido .... [" << user << "]" << endl;
        return -312;
    }

    if(strlen(pwd)<5)
    {
        cout << "[!] password invalido .... [" << pwd << "]" << endl;
        return -3121;
    }

    char *mail, *pmail;
    if(strlen(parmMail)<6)
    {
        cout << "[!] mail invalido .... [" << parmMail << "]" << endl;
        return -312312;
    }

        else
        mail=(char *) curl_easy_escape(NULL, parmMail, strlen(parmMail));


    if(strlen(parmpmail)<6)
    {
        cout << "[!] pmail invalido .... [" << parmpmail << "]" << endl;
        return -312131;
    }

        else
        pmail=(char *) curl_easy_escape(NULL, parmpmail, strlen(parmpmail));

    if(strlen(referer)<3)
    {
        cout << "[!] referer invalido .... [" << referer << "]" << endl;
        return -12312;
    }

    oPen obj;
    oPen::sCURL prms;
    strncpy(prms.proxy, "127.0.0.1:5321", 32);
    char capt[4], cook[128];
    Dialog dial;
    QImage img;

    prms=obj.curlme((char *)"http://venebux.com/register.php?r=", "/tmp/body.html", 1, prms, -1);

    while(prms.maxCOOK>=0)
    {
        if(strstr(prms.recvCookie[prms.maxCOOK], "PHPSESSID\t"))
        {
            strcpy(cook, "PHPSESSID=");
            strncat(cook, obj.corta(strstr(prms.recvCookie[prms.maxCOOK], "PHPSESSID"), 10, strlen(strstr(prms.recvCookie[prms.maxCOOK], "PHPSESSID"))-1), 512);
        }

    prms.maxCOOK=prms.maxCOOK--;
    }

    strncpy(prms.sendCookie, cook, 512);
    obj.curlme((char *)"http://venebux.com/image.php?", "/tmp/cap.png", 1, prms, -1);

    strcpy(prms.referer, "http://venebux.com/register.php?r=");
    strcpy(prms.postdata, "username=");
    strncat(prms.postdata, user, 512);
    strncat(prms.postdata, "&password=", 512);
    strncat(prms.postdata, pwd, 512);
    strncat(prms.postdata, "&cpassword=", 512);
    strncat(prms.postdata, pwd, 512);
    strncat(prms.postdata, "&email=", 512);
    strncat(prms.postdata, mail, 512);
    strncat(prms.postdata, "&cemail=", 512);
    strncat(prms.postdata, mail, 512);
    strncat(prms.postdata, "&country=", 512);
    strncat(prms.postdata, obj.randomcel(), 512);
    strncat(prms.postdata, "&pemail=", 512);
    strncat(prms.postdata, pmail, 512);
    strncat(prms.postdata, "&referer=", 512);
    strncat(prms.postdata, referer, 512);
    strncat(prms.postdata, "&code=", 512);

    img.load("/tmp/cap.png");
    dial.ui->lblImg->setPixmap(QPixmap::fromImage(img));
    dial.show();
    dial.exec();
    strncpy(capt, dial.ui->lineCaptcha->text().toLatin1(),4);
    strncat(prms.postdata, capt, 512);
    strncpy(prms.proxy, "127.0.0.1:5321", 32);
    prms.flagPST=1;

    obj.curlme((char *)"http://venebux.com/register.php", "/tmp/body.html", 1, prms, -1);

    if(strstr(prms.string, "Se ha registrado correctamente "))
    return 0;

        else
        return -213;
}

int loginVB(char login[], char pwd[])
{
    Dialog dial;
    QImage img;

    oPen obj;
    oPen::sCURL prms;
    char capt[24], cook[512], uri[512];

    prms.flagPST=-123;
    strncpy(prms.proxy, "127.0.0.1:5321", 32);
    prms=obj.curlme((char *)"http://venebux.com/login.php?r=", "/tmp/body.html", 1, prms, -1);

    while(prms.maxCOOK>=0)
    {
        if(strstr(prms.recvCookie[prms.maxCOOK], "PHPSESSID\t"))
        {
            strcpy(cook, "PHPSESSID=");
            strncat(cook, obj.corta(strstr(prms.recvCookie[prms.maxCOOK], "PHPSESSID"), 10, strlen(strstr(prms.recvCookie[prms.maxCOOK], "PHPSESSID"))-1), 512);
        }

    prms.maxCOOK=prms.maxCOOK--;
    }

    strcpy(prms.sendCookie, cook);
    strncpy(prms.referer, "http://venebux.com/login.php?r=", 512);
    strncpy(prms.proxy, "127.0.0.1:5321", 32);
    obj.curlme((char *)"http://venebux.com/image.php?", "/tmp/cap.png", 1, prms, -1);

    strcpy(prms.sendCookie, cook);
    strncpy(prms.referer, "http://venebux.com/login.php?r=", 512);
    strncpy(prms.proxy, "127.0.0.1:5321", 32);
    prms=obj.curlme((char *)"http://venebux.com/atencion/livehelp_js.php?eo=1&department=1&serversession=1&pingtimes=15", "/tmp/body.html", 1, prms, -1);

    char tmp[512];

    if(strstr(prms.string, "http://venebux.com/atencion/image.php?what=getstate&department=1&nowis="))
    {
        strncpy(uri,  strstr(prms.string, "http://venebux.com/atencion/image.php?what=getstate&department=1&nowis="), 512);
        strncat(tmp,  strtok(uri, "'"), 512);

        strcpy(prms.sendCookie, cook);
        strncpy(prms.referer, "http://venebux.com/login.php?r=", 512);
        strncpy(prms.proxy, "127.0.0.1:5321", 32);
        prms=obj.curlme(uri, "/tmp/body.html", 1, prms, -1);

        while(prms.maxCOOK>=0)
        {
            if(strstr(prms.recvCookie[prms.maxCOOK], "cookieid\t"))
            {
                strcat(cook, "; cookieid=");
                strncat(cook, obj.corta(strstr(prms.recvCookie[prms.maxCOOK], "cookieid"), 9, strlen(strstr(prms.recvCookie[prms.maxCOOK], "cookieid"))-1), 512);
            }

            if(strstr(prms.recvCookie[prms.maxCOOK], "cslhVISITOR\t"))
            {
                strcat(cook, "; cslhVISITOR=");
                strncat(cook, obj.corta(strstr(prms.recvCookie[prms.maxCOOK], "cslhVISITOR"), 12, strlen(strstr(prms.recvCookie[prms.maxCOOK], "cslhVISITOR"))-1), 512);
            }

        prms.maxCOOK--;
        }

        if(strstr(prms.string, "livehelp.php?what=chatinsession&department=1&cslhVISITOR="))
        {
            strncpy(uri,  strstr(prms.string, "livehelp.php?what=chatinsession&department=1&cslhVISITOR="), 512);
            strncat(tmp,  strtok(uri, "'"), 512);
            strcpy(uri, "http://venebux.com/atencion/");
            strncat(uri, obj.corta(tmp, 6, strlen(tmp)-1), 512);

            strncpy(prms.sendCookie, cook, 512);
            strncpy(prms.proxy, "127.0.0.1:5321", 32);
            strncpy(prms.referer, "referer: http://venebux.com/login.php?r=", 512);
            prms=obj.curlme(uri, "/tmp/body.html", 1, prms, -1);


              //http://venebux.com/atencion/image.php?what=getstate&department=1&nowis=

        }
    }

    img.load("/tmp/cap.png");
    dial.ui->lblImg->setPixmap(QPixmap::fromImage(img));
    dial.show();
    dial.exec();
    strncpy(capt, dial.ui->lineCaptcha->text().toLatin1(),24);

    strcpy(prms.postdata, "username=");
    strncat(prms.postdata, login, 255);
    strncat(prms.postdata, "&password=", 255);
    strncat(prms.postdata, pwd, 255);
    strncat(prms.postdata, "&code=", 255);
    strncat(prms.postdata, capt, 255);
    prms.flagPST=1;
    strncpy(prms.proxy, "127.0.0.1:5321", 32);
    strncpy(prms.sendCookie, cook, 512);

    prms=obj.curlme((char *)"http://venebux.com/login.php?r=", "/tmp/body.html", 1, prms, -1);

            strncat(cook, "; ", 512);
            strcpy(uri, "usNick=");
            strncat(uri, login, 512);
            strncat(uri, "; usPass=", 512);
            strncat(uri, pwd, 512);
            strcat(cook, uri);
            strncpy(prms.sendCookie, cook, 512);

    strcpy(uri, "http://venebux.com/");

    if(strstr(prms.string, "URL="))
    {
        strncpy(prms.string, strstr(prms.string, "URL="), 512);
        strncpy(prms.string, obj.corta(prms.string, 4, strlen(prms.string)-5), 512);
        strncat(uri, prms.string, 512);
        strncpy(prms.proxy, "127.0.0.1:5321", 32);

        prms=obj.curlme(uri, "/tmp/body.html", 1, prms, -1);

        strcpy(prms.referer, "http://venebux.com/members.php");
        strncpy(prms.proxy, "127.0.0.1:5321", 32);

        prms=obj.curlme("http://venebux.com/surf.php", "/tmp/body.html", 1, prms, -1);

        struct oPen::soPenXML loka=obj.filedump("/tmp/body.html", 1, "a", "a", 1);

        if(loka.max>0)
        {

            while(loka.max)
            {

                if(strstr(loka.var1[loka.max], "viewp.php"))
                strcpy(uri, "viewp.php");

                else if(strstr(loka.var1[loka.max], "view.php"))
                strcpy(uri, "view.php");

                else
                {
                    loka.max--;
                    continue;
                }

                strncpy(capt, uri, 24);
                strncat(capt, "viewp.php?ad=", 24);

                    if(!strcmp(strstr(loka.var1[loka.max], uri), capt))
                    {
                        loka.max--;
                        cout << "continue" << endl;
                        sleep(10);
                        continue;
                    }

                strcpy(uri, "http://venebux.com/");
                strncat(uri, loka.var1[loka.max], 512);

                strcpy(prms.referer, "http://venebux.com/surf.php");
                strcpy(prms.sendCookie, cook);
                strncpy(prms.proxy, "127.0.0.1:5321", 32);

                prms=obj.curlme(uri, "/tmp/body.html", 1, prms, -1);

                strcpy(prms.string, strstr(prms.string, "<input type=\"hidden\" name=\"verify\" value=\""));
                strcpy(prms.string, obj.corta(obj.RetNumber(prms.string), 0, 4));

                cout << "[+] Visitando... Por favor espere...  " << prms.string << endl;
                sleep(obj.random_enum(40, 70, 0));
                cout << "[+] DeadLine.! ^^" << endl;

                strcpy(loka.var1[loka.max], obj.corta(loka.var1[loka.max], 9, strlen(loka.var1[loka.max])-1));

                strcpy(uri, "http://venebux.com/success.php");
                strncat(uri, loka.var1[loka.max], 512);
                strncat(uri, "&verify=", 512);
                strncat(uri, prms.string, 512);

                prms.flagPST=1;
                strncpy(prms.proxy, "127.0.0.1:5321", 32);

                obj.curlme(uri, "/tmp/body.html", 1, prms, -1);
                prms.flagPST=-1;


            loka.max--;
            }
        }
    }

return 0;
}

void mimir()
{
    oPen obj;
    MYSQL_RES *resp;
    MYSQL_ROW rowMAIL, rowNAME, rowREFyPMAIL;
    char reu1[512], pass[8];

    //sleep(obj.random_enum(600, 1200, 0));

    resp=obj.mysql(NULL, "ganah", "usrganah", "57c2887bf3f2afce595192fcadf09d72127b496b1d4efd351c2f0f78635c", "select mail from avaible order by rand() limit 1", 0, 1);

        if(mysql_num_rows(resp))
        {
            rowMAIL=mysql_fetch_row(resp);

            resp=obj.mysql(NULL, "examples", "mierda", "7b49fd3c", "select nick from nickname order by rand() limit 1", 0, 1);
            rowNAME=mysql_fetch_row(resp);

            resp=obj.mysql(NULL, "ganah", "usrganah", "57c2887bf3f2afce595192fcadf09d72127b496b1d4efd351c2f0f78635c", "select user,pmail from account order by rand() limit 1", 0, 1);
            rowREFyPMAIL=mysql_fetch_row(resp);

                snprintf(pass, sizeof(pass), "%x", obj.random_enum(1287312, 1834697, 0));

            if(registerVB(rowNAME[0], pass, rowREFyPMAIL[1], rowMAIL[0], rowREFyPMAIL[0])==0)
            {
                strcpy(reu1, "delete from avaible where mail=\"");
                strncat(reu1, rowMAIL[0], 512);
                strncat(reu1, "\"", 512);
                obj.mysql(NULL, "ganah", "usrganah", "57c2887bf3f2afce595192fcadf09d72127b496b1d4efd351c2f0f78635c", reu1, 0, 1);

                strcpy(reu1, "insert into account values(\"");
                strncat(reu1, rowNAME[0], 512);
                strncat(reu1, "\", \"", 512);
                strncat(reu1, pass, 512);
                strncat(reu1, "\", \"", 512);
                strncat(reu1, rowREFyPMAIL[1], 512);
                strncat(reu1, "\")", 512);
                obj.mysql(NULL, "ganah", "usrganah", "57c2887bf3f2afce595192fcadf09d72127b496b1d4efd351c2f0f78635c", reu1, 0, 1);

            //sleep(obj.random_enum(600, 900, 0));
            }

        mysql_free_result(resp);
        }
}

int main(int num, char **param)
{

    QApplication app(num, param);

    oPen obj;

    MYSQL_RES *resp;
    MYSQL_ROW row;

    while(1)
    {

    resp=obj.mysql(NULL, "ganah", "usrganah", "57c2887bf3f2afce595192fcadf09d72127b496b1d4efd351c2f0f78635c", "select user,pwd from account order by rand()", 0, 1);

        while((row=mysql_fetch_row(resp)))
        {            
            cout << "Please wait ;)" << endl;
            mimir();

        loginVB(row[0], row[1]);
        }
    }

return 0;
}
