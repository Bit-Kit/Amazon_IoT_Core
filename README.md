Projekty z użyciem serwisu Amazon Internet of Things
===

1. [Po stronie AWS](#aws)
    1. [Tworzenie Rzeczy](#make_thing)
    2. [Tworzenie certyfikatu](#make_cred)
    3. [Tworzenie polityki](#make_policy)    
2. [Po stronie Rzeczy](#thing)
3. [Źródła](#zrodla)


<a name="aws"></a>
# Po stronie AWS

<a name="make_thing"></a>
## Tworzenie Rzeczy
Przechodzimy do serwisu **AWS IoT > Manage > Register a Thing**:
Wybieramy opcję **Create a single thing**, następnie wprowadzamy dowolną nazwę Rzeczy.

<a name="make_cred"></a>
## Tworzenie certyfikatu

Komunikacja między Twoją Rzeczą a AWS IoT jest chroniona za pomocą certyfikatów X.509. AWS IoT może wygenerować certyfikat dla ciebie lub możesz użyć własny certyfikatu X.509. W tym przykładzie certyfikat X.509 wygenerujemy za pomocą serwisu AWS IoT:
**AWS IoT > Secure > Certificates > Create a certificate > One-click certificate creation (recommended) > Create certificate**

Są 3 pliki do pobrania.

Nazwa pliku              | Opis
-------------------------|----------------------
2xxxxxxxx7.cert.pem      | A certificate for this thing
2xxxxxxxx7.public.key    | A public key
2xxxxxxxx7.private.key   | A private key

Certyfikaty należy **aktywować** przed użyciem, a następnie **przenieść** na urządzenie.

<a name="make_policy"></a>
## Tworzenie polityki
Do certyfikatu należy podpiąć "Politykę" (coś na kształt zapory ogniowej):

**AWS IoT > Secure > Create a policy**:
Najlepiej użyć nazwy urządzenia z przystawką *_policy* dla odróżniania zasad (policy).
Do pola **Add statements : Action** wprowadzamy opcję "*iot:\**", gdzie '\*' będzie dotyczyć wszystkich wydarzeń (*Subscribe,Connect i td.*)

Pole **Add statements : Resource ARN** prowadza się automatycznie: **arn:aws:iot:\<regon>:<id_konta_aws>:topic/replaceWithATopic**

W checkItem *"Effect"* zaznaczymy **Allow**

Dołączamy utworzoną politykę do certyfikatu:
**AWS IoT > Secure > Certificates**: _urworzony certyfikat_ > **Attach policy** > _utworzona polityka_

Ostatnim krokiem jest dołączenie certyfikata do Rzeczy:

**AWS IoT > Secure > Certificates**: _urworzony certyfikat_ > **Attach thing** > _utworzona rzecz.


<a name="thing"></a>
# Po stronie Rzeczy
Sprawdzamy wersję ssl klienta na urządzeniu:
    
    $ python
    >>> import ssl
    >>> ssl.OPENSSL_VERSION
    
  Wersja powinna być 1.0.1 lub wyżej.


Instalujemy AWS SDK:

    git clone https://github.com/aws/aws-iot-device-sdk-python.git
    cd aws-iot-device-sdk-python
    sudo python setup.py install
Tworzymy folder do projektów:

    mkdir ~/IoT
    cd ~/IoT/
 
  Pobieramy certyfikat Amazon RSA 2048 bitowy klucz:
  
    sudo curl https://www.amazontrust.com/repository/AmazonRootCA1.pem > root-CA.crt
   
Tworzymy skrypt Python:

    touch examle.py
    nano examle.py
    
Wklejamy przykładowy kod:

    #Importowanie biblioteki
    from AWSIoTPythonSDK.MQTTLib import AWSIoTMQTTClient
    #
    myMQTTClient = AWSIoTMQTTClient("basicPubSub")
    #Pierwszy argument to "EndPoint",Subscription topic można sprawdzić poleceniem "$ aws iot describe-endpoint" w terminale
    #Drugi argument to używany port protokołu MQTT + SSL (8883)
    myMQTTClient.configureEndpoint("<Twój_EndPoint>-ats.iot.us-east-1.amazonaws.com", 8883) #443
    #Należy podać certyfikat AWS("root-CA.crt"), klucz prywatny, certyfikat Rzeczy
    myMQTTClient.configureCredentials("root-CA.crt","2xxxxxxxx7.private.key","2xxxxxxxx7.cert.pem")
    myMQTTClient.configureOfflinePublishQueueing(-1)  # Infinite offline Publish queueing
    myMQTTClient.configureDrainingFrequency(2)  # Draining: 2 Hz
    myMQTTClient.configureConnectDisconnectTimeout(10)  # 10 sec
    myMQTTClient.configureMQTTOperationTimeout(5)  # 5 sec
    myMQTTClient.connect()
    #Pierwszy argument to ścieżka do tematu, można użyć tej
    #Drugi argument to komunikat
    #Trzeci to QoS (0;1)
    myMQTTClient.publish("Test/moja_rzecz", "Hello. Im working!", 1)
    myMQTTClient.disconnect()
    
W przeglądarce wchodzimy do 
**AWS IoT > Test : Subscription** topic, gdzie podajemy nazwe tematu, *(myMQTTClient.publish("Test/moja_rzecz", "Hello. Im working!", 1))*

Na urządzeniu wówczas uruchomiamy skrypt:

    python example.py

Obserwujemy w przeglądarce otszymany komunikat

    



---
<a name="zrodla"></a>
### Źródła 

* [AWS IoT Device SDK for Python](https://docs.aws.amazon.com/iot/latest/developerguide/iot-sdks.html)
* [Security and Identity for AWS IoT](https://docs.aws.amazon.com/iot/latest/developerguide/iot-security-identity.html)
* [AWSIoTPythonSDK 1.4.1 documentation](https://s3.amazonaws.com/aws-iot-device-sdk-python-docs/html/index.html)
* [X.509 Certificates and AWS IoT](https://docs.aws.amazon.com/iot/latest/developerguide/managing-device-certs.html#server-authentication)
