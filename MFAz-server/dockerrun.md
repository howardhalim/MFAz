sudo docker build -t mfaz-server .

sudo docker run -p 8080:9090 mfaz-server

ngrok http http://localhost:8080

https://55b8-158-140-138-91.ngrok-free.app 8080
https://f397-158-140-138-91.ngrok-free.app 5000