FROM node:8.16.0-alpine

COPY . /openvslam-viewer/

RUN set -x && \
  cd /openvslam-viewer/ && \
  npm install
# --registry=https://registry.npm.taobao.org

ENTRYPOINT ["node", "/openvslam-viewer/app.js"]
