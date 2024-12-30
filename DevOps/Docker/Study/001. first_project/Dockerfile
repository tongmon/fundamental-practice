# base image
FROM node:14

# working directory in container
WORKDIR /app

# copy package.json to working directory in container
COPY package.json .

# execute `npm install` command in container
RUN npm install

# copy current codes to working directory in container
COPY . .

# expose specific port to other computer so that other computer can communicate with this container
EXPOSE 3000

# execute node command
CMD [ "node", "app.mjs"]

# you can execute this dockerfile with `docker build .` command in current project directory
# then you can find image id from `writing image sha256:c08703ee8406c5170f831bd909588905570c5df1f36d7a9ce785704bfde43f9e` this line
# After that, you can run container by running `docker run c08703ee8406c5170f831bd909588905570c5df1f36d7a9ce785704bfde43f9e` command
# but in this project we need to connect between container with local computer so have to add `-p local_port:container_port` command
# container port exposed is 3000 and local port that used in code is 3000 so final command looks like below
# `docker run -p 3000:3000 c08703ee8406c5170f831bd909588905570c5df1f36d7a9ce785704bfde43f9e`
# as a result, command template look like this `docker run -p {localport_whatever_you_want}:{docker_exposed_port} {IMAGE_ID}`
# After execute above command, you can enter `http://localhost:3000/` link in your brower
# When you want to stop docker image, then open other terminal and execute `docker ps`, then you can find current running images and their names
# copy the name of image that you want to stop and execute `docker stop {IMAGE_NAME}` command to stop the docker image that you want

# Docker Images: Blueprint for Docker Container, this image contains js files, nodeJS ... something like code or tools or env settings
# Docker Container: Actual Running Process or Application
# Therefore, One Images can provide multiple Container

# You can find image presets in https://hub.docker.com/

# `docker ps -a` shows all images in docker

# `docker run -it {IMAGE}` runs docker image in interactive mode, so you can interact with image via terminal