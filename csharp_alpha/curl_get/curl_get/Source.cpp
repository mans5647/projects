#include <iostream>
#include <curl/curl.h> 

int main(void)
{
	CURL* handle;
	handle = curl_easy_init();
	if (handle)
	{
		
		curl_easy_setopt(handle, CURLOPT_USERNAME, "mansurgal3005@mail.ru");
		/*curl_easy_setopt(handle, CURLOPT_VERBOSE, 1L);*/
		curl_easy_setopt(handle, CURLOPT_PASSWORD, "hR2PBi1JxEd7fGrx38W4");
		curl_easy_setopt(handle, CURLOPT_URL, "imap. ");
		CURLcode res = curl_easy_perform(handle);
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
	}
}