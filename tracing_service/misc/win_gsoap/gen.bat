wsdl2h -o generated\ImTrcrService.h  ..\imtrcr_soap.wsdl
soapcpp2 generated\ImTrcrService.h -S -d .\generated

PAUSE