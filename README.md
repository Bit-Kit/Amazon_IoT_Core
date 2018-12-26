Projekty z użyciem serwisu Amazon Internet of Things
===

1. [Po stronie AWS](#aws)
    1.[Tworzenie Rzeczy](#make_thing)
    2.[Tworzenie certyfikatu](#make_cred)
    3.[Tworzenie Polityki](#make_policy)    
2. [Po stronie Rzeczy](#thing)
3. [Źródła](#zrodla)


<a name="aws"></a>
# Po stronie AWS

<a name="make_thing"></a>
#### Tworzenie Rzeczy
Przechodzimy do serwisu **AWS IoT > Manage > Register a Thing**:
Wybieramy opcję **Create a single thing**, następnie wprowadzamy dowolą nażwę naszej rzeczy.

<a name="make_cred"></a>
#### Tworzenie certyfikatu
Dalej strona poprosi wybrać sposób utwożenia certyfikatu. 
Komunikacja między Twoją Rzeczą a AWS IoT jest chroniona za pomocą certyfikatów X.509. AWS IoT może wygenerować certyfikat dla ciebie lub możesz użyć własny certyfikatu X.509. W tym przykładzie certyfikat X.509 wygenerujemy za pomocą serwisu AWS IoT, wybierając opcję **One-click certificate creation (recommended)**.
Wygenerowane zostaną następne pliki:

Nazwa pliku              | Opis
-------------------------|----------------------
2xxxxxxxx7.cert.pem      | A certificate for this thing
2xxxxxxxx7.public.key    | A public key
2xxxxxxxx7.private.key   | A private key

Certyfikaty należy **aktywować** przed użyciem, a nestępnie **przenieść** na urządzenie.

<a name="make_policy"></a>
#### Tworzenie Polityki
Jak już aktywowaliśmy/przenieśliśmy pliki, należy utwożyć "politykę" (coś na krztałt zapory ogniowej) i dołączyć do utworzonego cetryfikata:

**AWS IoT > Secure > Create a policy**:
Najlepiej użyć nazwy urządzenia z przystawką *_policy* dla odróżniania zasad.
Do pola **Add statements : Action** wprowadzamy opcję "*iot:\**", gdzie '\*' będzię dotyczyć wszystkich wydarzeń (*Subscribe,Connect i td.*)

Pole **Add statements : Resource ARN** prowadza się automatycznie: **arn:aws:iot:\<regon>:<id_konta_aws>:topic/replaceWithATopic**

W checkItem *"Effect"* zaznaczymy **Allow**

Po utwożeniu, dołączamy politykę do certyfikatu: **AWS IoT > Secure > Certificates**: _urworzony certyfikat_ > **Attach policy** > _urworzona polityka_.

Ostatnim krokiem jest dołączenie certyfikata do Rzeczy:

**AWS IoT > Secure > Certificates**: _urworzony certyfikat_ > **Attach thing** > _urworzona rzecz.



<a name="thing"></a>
# Po stronie Rzeczy

---
<a name="zrodla"></a>
### Źródła 

* [AWS IoT Device SDK for Python](https://docs.aws.amazon.com/iot/latest/developerguide/iot-sdks.html)
* [Security and Identity for AWS IoT](https://docs.aws.amazon.com/iot/latest/developerguide/iot-security-identity.html)
* [AWSIoTPythonSDK 1.4.1 documentation](https://s3.amazonaws.com/aws-iot-device-sdk-python-docs/html/index.html)
