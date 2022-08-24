docker rmi aaronv70/python-client

docker build -t aaronv70/python-client .

docker push aaronv70/python-client

kubectl delete deployment client-deployment

kubectl delete service client-svc-ext

