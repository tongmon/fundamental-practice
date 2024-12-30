- docker ps -a
  show all containers which is running or not

- docker ps
  show running containers

- docker run {IMAGE-NAME or IMAGE-ID}
  create new container based on selected image and execute it with attached mode, so the current terminal is blocked by new container

- docker run -d {IMAGE-NAME or IMAGE-ID}
  create new container based on selected image with detached mode

- docker run -p {LOCAL-PORT}:{EXPOSED-PORT}
  create new container based on selected image with exposed port

- docker start {CONTAINER-NAME or CONTAINER-ID}
  start pre-exsist container in detached mode, so the container is executed in the background

- docker start -a {CONTAINER-NAME or CONTAINER-ID}
  start pre-exsist container in attached mode

- docker attach {CONTAINER-NAME or CONTAINER-ID}
  make selected running container to attached mode

- docker logs {CONTAINER-NAME or CONTAINER-ID}
  fetch logs from selected container

