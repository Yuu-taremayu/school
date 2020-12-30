import http.client
import smtplib
from email.mime.text import MIMEText
from email.mime.application import MIMEApplication
from email.mime.multipart import MIMEMultipart
from email.utils import formatdate

def save_html():
    url = 'abehiroshi.la.coocan.jp'
    httpConnection = http.client.HTTPConnection(url)
    httpConnection.request('GET', '/')
    res = httpConnection.getresponse()
    print('HTTP Status:', res.status)
    data = res.read()
    with open('abehiroshi.html', 'w') as f:
        f.write(str(data))

def create_mail(_fromAddress, _toAddress):
    sub = 'Information Communication System, 25, Yu Miura'
    text = 'Test mail from Yu'
    msg = MIMEMultipart()
    msg.attach(MIMEText(text))
    msg['Subject'] = sub
    msg['From'] = _fromAddress
    msg['To'] = _toAddress
    msg['Date'] = formatdate(localtime=True)
    with open('abehiroshi.html', 'r') as f:
        mb = MIMEApplication(f.read())
    mb['Content-Disposition'] = 'attachment; filename=abehiroshi.html'
    msg.attach(mb)
    print(msg)
    return msg

def send_mail(_fromAddress, _toAddress, _msg):
    password = 'PASSWORD'
    with smtplib.SMTP('smtp.office365.com', 587) as smtp:
        smtp.set_debuglevel(1)
        smtp.ehlo()
        smtp.starttls()
        smtp.ehlo()
        smtp.login(_fromAddress, password)
        smtp.sendmail(_fromAddress, _toAddress, _msg.as_string())

def main():
    fromAddress = 'j16437@kisarazu.kosen-ac.jp'
    toAddress = 'j16437@kisarazu.kosen-ac.jp'
    save_html()
    msg = create_mail(fromAddress, toAddress)
    send_mail(fromAddress, toAddress, msg)

if __name__ == '__main__':
    main()
