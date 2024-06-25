# Based on https://github.com/dobtc/bitcoin/blob/v25.2/Dockerfile
FROM debian:bookworm-slim

ARG TAG
ARG REPO
ARG IS_RELEASE=false
ARG TARGETOS
ARG TARGETARCH

ARG UID=1001
ARG GID=1001

ARG DEBCONF_NOWARNINGS="yes"
ARG DEBIAN_FRONTEND="noninteractive"
ARG DEBCONF_NONINTERACTIVE_SEEN="true"

RUN groupadd --gid ${GID} bitcoin \
    && useradd --create-home --no-log-init -u ${UID} -g ${GID} bitcoin \
    && apt-get update -y \
    && apt-get --no-install-recommends -y install jq curl gnupg gosu ca-certificates libevent-dev \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/* \
    && if ${IS_RELEASE}; then \
         echo "BIN_ARCH: $BIN_ARCH" ; \
         echo "curl -Ls https://github.com/${REPO}/releases/download/${TAG}/bitcoin-${TAG}-${TARGETOS}-${TARGETARCH}.tar.gz -o /${TARGETOS}-${TARGETARCH}.tar.gz" ; \
         curl -Ls https://github.com/${REPO}/releases/download/${TAG}/bitcoin-${TAG}-${TARGETOS}-${TARGETARCH}.tar.gz -o /${TARGETOS}-${TARGETARCH}.tar.gz ; \
       fi

ENV BITCOIN_DATA=/home/bitcoin/.bitcoin
ENV PATH=/opt/bitcoin/bin:$PATH

SHELL ["/bin/bash", "-c"]

# A tar.gz will only be copied in if one exists in context (typically the case when IS_RELEASE=false)
COPY --chmod=755 *${TARGETOS}-${TARGETARCH}*.tar.gz .
RUN tar -xzf ./*.tar.gz -C /opt

COPY --chmod=755 entrypoint.sh /entrypoint.sh

VOLUME ["/home/bitcoin/.bitcoin"]

# REST interface
EXPOSE 8080

# P2P network (mainnet, testnet & regtest respectively)
EXPOSE 8333 18333 18444

# RPC interface (mainnet, testnet & regtest respectively)
EXPOSE 8332 18332 18443

HEALTHCHECK --interval=300s --start-period=60s --start-interval=10s --timeout=20s CMD gosu bitcoin bitcoin-cli -rpcwait -getinfo || exit 1

ENTRYPOINT ["/entrypoint.sh"]

RUN bitcoind -version

CMD ["bitcoind"]
