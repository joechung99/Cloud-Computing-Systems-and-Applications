var http = require('http')

requestToken = function() {
    var options = {
        host: '192.168.0.232',
        port: 5000,
        path: '/v3/auth/tokens',
        method: 'POST',
        headers: {
            'Content-type': 'application/json',
        }
    }
    var req = http.request(options, function(res) {
        res.setEncoding('utf8')
        res.on('data', function(chunk) {
            console.log(res.headers)
        })
    })
    var postData = JSON.stringify({
        'auth': {
            'identity': {
                'methods': ['password'],
                'password': {
                    'user': {
                        'name': 'admin',
                        'domain': {
                            'name': 'Default'
                        },
                        'password': 'cloud'
                    }
                }
            },
            'scope': {
                'project': {
                    'name': 'admin',
                    'domain': {
                        'name': 'Default'
                    }
                }
            }
        }
    })
    req.end(postData)
}

requestToken()