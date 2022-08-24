
#!/bin/bash


docker rm $(docker ps -f status=exited -q)
docker rmi aaronv70/c-server
docker build -t aaronv70/c-server .
docker push aaronv70/c-server
kubectl delete deployment server-deployment
kubectl delete service server-svc-ext
