In this MFAz server, no blockchain is used for the demo.

- Uses Miracl Library like the [/Gateway_C++]. Please refer to its Readme.md file if have troubled setting up Miracl Library

- "cppcms" framework is used for this MFAz server ("https://github.com/artyom-beilis/cppcms")
    all cppcms file is provided in the MFAz-server directory. If having trouble running the server please refer to cppcms build documentation ("http://cppcms.com/wikipp/en/page/cppcms_1x_build")

- libcurl library is also used which will be handled by docker.

- [Dockerfile] is provided and will be used to run the MFAz-server

# To Start:
1. Run "test.sh" to recompile the application to make sure everything is good to go
2. "sudo docker build -t mfaz-server ." to build the [Dockerfile]
3. "sudo docker run -p 8080:9090 mfaz-server" to run the MFAz server

4. (Refer to [/gateway-server] Readme.md file) host the MFAz-server to ngrok for cross device access


# NB:
1. To reset the MFAz data, delete "bf.txt" file and all the file inside "secret_seed" folder (do not delete the folder)
