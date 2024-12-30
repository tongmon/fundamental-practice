FROM python

WORKDIR /app

COPY . /app

CMD [ "python", "rng.py" ]

# you should run the container made with this image with `-it` option! (ex. docker run -it 15e99b43e714f)
# without that option, you can't type in the keyboard data to the docker container.
# and the rng.py file contains the `input` python function.
# so use `-it` option and turn your container to interactive mode.

# if you want to start again the container made with this image, execute command with `-ai` option. (ex. docker start -ai funny_spence)
# `-ai` means attached and interactive mode