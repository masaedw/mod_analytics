/* 
**  mod_analytics.c -- Apache sample analytics module
**  [Autogenerated via ``apxs -n analytics -g'']
**
**  To play with this sample module first compile it into a
**  DSO file and install it into Apache's modules directory 
**  by running:
**
**    $ apxs -c -i mod_analytics.c
**
**  Then activate it in Apache's httpd.conf file for instance
**  for the URL /analytics in as follows:
**
**    #   httpd.conf
**    LoadModule analytics_module modules/mod_analytics.so
**    <Location /analytics>
**    SetHandler analytics
**    </Location>
**
**  Then after restarting Apache via
**
**    $ apachectl restart
**
**  you immediately can request the URL /analytics and watch for the
**  output of this module. This can be achieved for instance via:
**
**    $ lynx -mime_header http://localhost/analytics 
**
**  The output should be similar to the following one:
**
**    HTTP/1.1 200 OK
**    Date: Tue, 31 Mar 1998 14:42:22 GMT
**    Server: Apache/1.3.4 (Unix)
**    Connection: close
**    Content-Type: text/html
**  
**    The sample page from mod_analytics.c
*/ 

#include <iostream>
#include "httpd.h"
#include "http_config.h"
#include "http_protocol.h"
#include "ap_config.h"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/lexical_cast.hpp>

using namespace boost::uuids;

static std::string make_uuid_str()
{
    static auto gen = random_generator();
    const uuid id = gen();
    return boost::lexical_cast<std::string>(id);
}

/* The sample content handler */
static int analytics_handler(request_rec *r)
{
    if (strcmp(r->handler, "analytics")) {
        return DECLINED;
    }
    r->content_type = "text/html";

    std::string id_str = make_uuid_str();
    std::string sample = std::string("The sample page from mod_analytics.cpp ") + id_str + "\n";

    if (!r->header_only)
        ap_rputs(sample.c_str(), r);
    return OK;
}

static void analytics_register_hooks(apr_pool_t *p)
{
    ap_hook_handler(analytics_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

/* Dispatch list for API hooks */

extern "C" {
module AP_MODULE_DECLARE_DATA analytics_module = {
    STANDARD20_MODULE_STUFF, 
    NULL,                  /* create per-dir    config structures */
    NULL,                  /* merge  per-dir    config structures */
    NULL,                  /* create per-server config structures */
    NULL,                  /* merge  per-server config structures */
    NULL,                  /* table of config file commands       */
    analytics_register_hooks  /* register hooks                      */
};
}
