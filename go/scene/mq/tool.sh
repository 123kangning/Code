# 列出所有topic
./kafka-topics.sh --list --bootstrap-server localhost:9092
# 展示具体topic的详情
./kafka-topics.sh --describe --bootstrap-server localhost:9092 --topic topic-A
