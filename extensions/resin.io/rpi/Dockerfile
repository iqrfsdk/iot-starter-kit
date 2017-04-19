FROM resin/rpi-raspbian:latest
ENV INITSYSTEM on

MAINTAINER n/a

# update repos
RUN	echo "deb http://repos.iqrfsdk.org/raspbian jessie testing" | sudo tee -a /etc/apt/sources.list.d/iqrf-daemon.list \
	&& apt-key adv --keyserver keyserver.ubuntu.com --recv-keys F973CFCE6B3BE25C
        
RUN	apt-get update \
	&& apt-get install -y iqrf-daemon \
	&& apt-get clean \
	&& rm -rf /var/lib/apt/lists/*

WORKDIR /opt

ADD	http://www.random.org/strings/?num=10&len=8&digits=on&upperalpha=on&loweralpha=on&unique=on&format=plain&rnd=new uuid.txt
RUN	date | tee build.txt

COPY	iqrf-daemon/config /etc/iqrf-daemon

ADD init.sh /init.sh

ENTRYPOINT ["/init.sh"]
