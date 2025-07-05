#include <string.h>
#include "esp_log.h"
#include "esp_http_server.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"

static const char *TAG = "HTTP_FEEDBACK";

// HTML form page
const char *form_html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>"
"<title>Feedback</title><style>"
"body{background:#f4f4f4;font-family:sans-serif;display:flex;justify-content:center;align-items:center;height:100vh;margin:0}"
".form-container{background:#fff;padding:30px;border-radius:10px;box-shadow:0 0 10px rgba(0,0,0,0.1)}"
"h2{color:#333}input,textarea{width:100%;padding:10px;margin:10px 0;border:1px solid #ccc;border-radius:5px}"
"button{background:#007BFF;color:#fff;padding:10px 20px;border:none;border-radius:5px;cursor:pointer}"
"button:hover{background:#0056b3}"
"</style></head><body>"
"<div class='form-container'><h2>Feedback Form</h2>"
"<form method='POST' action='/submit'>"
"<input type='text' name='name' placeholder='Your Name' required>"
"<input type='email' name='email' placeholder='Your Email' required>"
"<textarea name='message' placeholder='Your Feedback' rows='4' required></textarea>"
"<button type='submit'>Send Feedback</button>"
"</form></div></body></html>";

// Thank you page
const char *thank_you_html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>"
"<title>Thank You</title><style>body{background:#e0ffe0;font-family:sans-serif;text-align:center;padding-top:50px}"
"h1{color:#28a745}</style></head><body><h1>Thank you for your feedback!</h1></body></html>";

esp_err_t form_get_handler(httpd_req_t *req) {
    httpd_resp_send(req, form_html, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

esp_err_t submit_post_handler(httpd_req_t *req) {
    char buf[512];
    int ret = httpd_req_recv(req, buf, (req->content_len < sizeof(buf) - 1) ? req->content_len : sizeof(buf) - 1);
    if (ret <= 0){
         return ESP_FAIL;
    }
    buf[ret] = '\0';

    ESP_LOGI(TAG, "Received POST data: %s", buf);  // Log the feedback

    httpd_resp_send(req, thank_you_html, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

void start_webserver(void) {
     httpd_config_t config = HTTPD_DEFAULT_CONFIG();


    httpd_handle_t server = NULL;
    if (httpd_start(&server, &config) == ESP_OK) {
        httpd_uri_t form = {
            .uri = "/",
            .method = HTTP_GET,
            .handler = form_get_handler,
            .user_ctx = NULL
        };
        httpd_uri_t submit = {
            .uri = "/submit",
            .method = HTTP_POST,
            .handler = submit_post_handler,
            .user_ctx = NULL
        };
        httpd_register_uri_handler(server, &form);
        httpd_register_uri_handler(server, &submit);
        ESP_LOGI(TAG, "HTTP server started");
    }
}

void wifi_call() {
    esp_netif_create_default_wifi_ap();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);
    wifi_config_t wifi_config = {
        .ap = {
            .ssid = "XIAO-ESP",
            .ssid_len = strlen("XIAO-ESP"),
            .channel = 1,
            .password = "esp32only",
            .max_connection = 4,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK
        },
    };
   

    esp_wifi_set_mode(WIFI_MODE_AP);
    esp_wifi_set_config(WIFI_IF_AP, &wifi_config);
    esp_wifi_start();
    ESP_LOGI(TAG, "WiFi AP started. SSID:XIAO-ESP");
}

void app_main(void) {
    nvs_flash_init();
    esp_netif_init();
    esp_event_loop_create_default();
    wifi_call();
    start_webserver();
}
