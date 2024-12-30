# base image setting
# name of `node` image preset should be already in docker.hub 
FROM node

WORKDIR /app

# Before execute the `RUN npm install`, It is good to execute `COPY package.json /app` first.
# Evertime you build this image, if the package.json is not changed, `npm install` will not executed unnecessarily.
# `npm install` will only execute when new package is needed or package list is modified.
COPY package.json /app

# run specific command in directory setted in `WORKDIR`
# the command will execute when the image start to build, something like `docker build .` command
# so this `RUN` is usually used for installing library
RUN npm install

# first arg is for local working directory location
# second arg is for docker image working directory location
# It is recommand to use some custom named folder in second arg
COPY . /app

# let docker know specific local port to communicate with user's computer.
EXPOSE 80

# run specific command after creating and executing the container (different from `RUN`)
# so `CMD` is for 'docker run' command
CMD [ "node", "server.js" ]

# if you are done with writting dockerfile, just follow `commands` listed below.
# `docker build .`
# `docker run -p 3000:80 {IMAGE_ID}`
# enter the http://localhost:3000/ link
# `docker stop {CONTAINER_NAME}`

# if you change your code, you need to rebuild your docker image once again to apply the changes.
# Image is locked after you build the image, so you can't modify or apply changes after image is locked.

# Docker is layer based image system
# so every after executing every single the command line, docker makes each of image layer.
# for example, if Dockerfile has `FROM`, `WORKDIR`, `COPY` command line, then first layer is created from `FROM` command
# and second layer is created from `WORKDIR` command so at this point this layer has the state where `FROM` and `WORKDIR` are executed.
# As a matter of course, the final layer is created from `COPY`
# and when each layer is created, image is locked every time so all of the layers created from image are read-only.
# After create all of the layer, container layer covers the whole layers, and container layer is read-write mode.

# because of the layer system, if docker detect there is no change after execute specific command, then docker doesn't execute that command
# but instead of that, docker just use the layer which is created in the past.

# Every each containers from one image are indepedent and can't know each others so there is no shared data between them.