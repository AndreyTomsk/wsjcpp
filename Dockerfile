# Automaticly generated by wsjcpp@v0.0.1
# for-release wsjcpp:v0.0.1
FROM wsjcpp-for-build:latest

COPY . /root/sources
RUN mkdir -p tmp.docker && cd tmp.docker && cmake .. && make

FROM wsjcpp-for-release:latest

COPY --from=0 /root/sources/wsjcpp /usr/bin/wsjcpp
