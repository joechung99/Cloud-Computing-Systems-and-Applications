import requests
import json
def gettoken():
    header = {'content-type': 'application/json'}
    data = {
        "auth": {
            "identity": {
                "methods": [
                    "password"
                ],
                "password": {
                    "user": {
                        "name": "admin",
                        "domain": {
                            "name": "Default"
                        },
                        "password": "cloud2016"
                    }
                }
            },
            "scope":{
                "project":{
                    "name":"admin",
                    "domain":{
                        "name":"Default"
                    }
                }
            }
        }
    }
    response = requests.post('http://192.168.0.18:5000/v3/auth/tokens',headers=header,data = json.dumps(data))
    response_dic = response.json()
    response_text = response.headers
    token=response.headers['X-Subject-Token']
    return token
def getimageid(token):
    header = {'Content-Type': 'application/json','X-Auth-Token':token}
    response = requests.get('http://192.168.0.18:9292/v2.0/images',headers=header)
    response_dic = response.json()
    return (response_dic['images'][0]['id'])
def getflavor(token):
    header = {'Content-Type': 'application/json','X-Auth-Token':token}
    response = requests.get('http://192.168.0.18:8774/v2.1/flavors',headers=header)
    response_dic = response.json()
    return (response_dic['flavors'][4]['id'])
def createserver(token,imagesid,flavorsid):
    header = {'Content-Type': 'application/json','X-Auth-Token':token}
    data = {
        "server" : {
            "accessIPv4": "1.2.3.4",
            "accessIPv6": "80fe::",
            "name" : "new-server-pythontest",
            "imageRef" : imagesid,
            "flavorRef" : flavorsid,
            "availability_zone": "nova",
            "OS-DCF:diskConfig": "AUTO",
            "metadata" : {
                "My Server Name" : "Apache1"
            },
        "personality": [
            {
                "path": "/etc/banner.txt",
                "contents": "ICAgICAgDQoiQSBjbG91ZCBkb2VzIG5vdCBrbm93IHdoeSBp dCBtb3ZlcyBpbiBqdXN0IHN1Y2ggYSBkaXJlY3Rpb24gYW5k IGF0IHN1Y2ggYSBzcGVlZC4uLkl0IGZlZWxzIGFuIGltcHVs c2lvbi4uLnRoaXMgaXMgdGhlIHBsYWNlIHRvIGdvIG5vdy4g QnV0IHRoZSBza3kga25vd3MgdGhlIHJlYXNvbnMgYW5kIHRo ZSBwYXR0ZXJucyBiZWhpbmQgYWxsIGNsb3VkcywgYW5kIHlv dSB3aWxsIGtub3csIHRvbywgd2hlbiB5b3UgbGlmdCB5b3Vy c2VsZiBoaWdoIGVub3VnaCB0byBzZWUgYmV5b25kIGhvcml6 b25zLiINCg0KLVJpY2hhcmQgQmFjaA=="
            }
        ],
        "security_groups": [
            {
                "name": "default"
            }
        ],
        "user_data" : "IyEvYmluL2Jhc2gKL2Jpbi9zdQplY2hvICJJIGFtIGluIHlvdSEiCg=="
        },
        "OS-SCH-HNT:scheduler_hints": {
            "same_host": "48e6a9f6-30af-47e0-bc04-acaed113bb4e"
        }
    }
    
        
    response = requests.post('http://192.168.0.18:8774/v2.1/servers',headers=header,data=json.dumps(data))
    response_dic = response.json()
    print (response_dic)
if __name__ == '__main__':
    token=gettoken()
    imagesid=getimageid(token)
    flavorsid=getflavor(token)
    createserver(token,imagesid,flavorsid)