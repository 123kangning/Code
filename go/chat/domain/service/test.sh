curl --location --request GET 'http://localhost:80/v1/api/ai/refresh' \
--header 'Cookie: wx=df9813f23a8bd4fd943f98c073bd2055mymyxyxbbq; xesId=eb4db07dd4b0ce9b17c7c0c390cce42c; prelogid=9e6c0d367902d54e3c6889f0f0e05bc9; tal_token=tal173aLsCFlymxX1jSfZsD6fQplbjyuDXR1EyZN7qeam9-uwp25o1unkK0_TsWcNys14g_4FJs4WTC4IzECZBsVYaMvjgBRuGRkzKrspFKbzlW7penyRauAAjqlFG9MkhGeYztwmuFPKJ4ZNyDhfUxuy4T0cH4n2419gYEgKvK-emQ18mkI2y3C4JPl4OM3N4GlmyX1TCVrD-XiDbZtNwu_RuNPTFOIpL9Zv0CEXmq4EpQ8W2pJzr5VeGxByg2pSwHSbpauMQAzIQSzaJW3vs_XqKtRPMUM-DMCt0avUrTB8fdIPjg; tal_token=tal173V3bcvzaw3i0QVnYADbwD-tFXblX7YLt6UI0y8Wfq3MeY13Umfluzr7mYAzRlzBMQ1yjROWWkxUOsV1r8CFLJHde8Ykww93ZDam3P4xAHlQqsz59uYtyTpKRO6FPrXCxpKI_XchP7zlzUWqqjjpaHGjwUD8UGeTS11g8BwOqvRoomkI2y3C4JPl4OM3N4GlmyX1TCVrD-XiDbZtNwu_RuNPTFOIpL9Zv0CEXmq4EpQ8W2pJzr5VeGxByg2pSwHSbpauMQAzIQSzaJW3vs_XqKtRPMUM-DMCt0avUrTB8fdIPjg' \
--header 'User-Agent: Apifox/1.0.0 (https://apifox.com)' \
--header 'Accept: */*' \
--header 'Host: localhost:80' \
--header 'Connection: keep-alive' \
--header 'ContentType: text/event-stream'


curl --location --request POST 'http://localhost:80/v1/api/ai/chat' \
--header 'Cookie: wx=df9813f23a8bd4fd943f98c073bd2055mymyxyxbbq; xesId=eb4db07dd4b0ce9b17c7c0c390cce42c; prelogid=9e6c0d367902d54e3c6889f0f0e05bc9; tal_token=tal173aLsCFlymxX1jSfZsD6fQplbjyuDXR1EyZN7qeam9-uwp25o1unkK0_TsWcNys14g_4FJs4WTC4IzECZBsVYaMvjgBRuGRkzKrspFKbzlW7penyRauAAjqlFG9MkhGeYztwmuFPKJ4ZNyDhfUxuy4T0cH4n2419gYEgKvK-emQ18mkI2y3C4JPl4OM3N4GlmyX1TCVrD-XiDbZtNwu_RuNPTFOIpL9Zv0CEXmq4EpQ8W2pJzr5VeGxByg2pSwHSbpauMQAzIQSzaJW3vs_XqKtRPMUM-DMCt0avUrTB8fdIPjg' \
--header 'Content-Type: application/json' \
--data-raw '{
    "session_id": "1b7b97d5b71d42129fca297573ae9a71",
    "is_init": false,
    "messages": "简要说一下依赖注入"
}'


curl --location --request GET 'http://inntest.xue.xiwang.com/practice-page/v1/api/ai/refresh' \
--header 'Cookie: xesId=eb4db07dd4b0ce9b17c7c0c390cce42c; userGrade=2; wx=d13794f6bffc06ce045c85fb87167db0m9ss0sbsyq; user_token=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhY2NvdW50Ijoid193YW5na2FuZ25pbmciLCJhY2NvdW50X25hbWUiOiIiLCJlbWFpbCI6Indfd2FuZ2thbmduaW5nQHhpd2FuZy5jb20iLCJuYW1lIjoi546L5bq35a6BIiwid29ya2NvZGUiOiJXMDE2NTIwIiwidGVhY2hlcl9pZCI6MCwicm9sZV9pZCI6IiIsImV4cCI6MTczMzc0NDk0OSwiaXNzIjoieGl3YW5nIn0.bUfxYJsQpxX-8XdWo6aCTewpWwgJmBQ1rAWDJ_ufav8; acw_tc=7b7dd89817333879815016719e0cdad98d5494e2d94eba0f0202dae846; cdn_sec_tc=7b7dd89817333879815016719e0cdad98d5494e2d94eba0f0202dae846; prelogid=2ccc5032c530cf886f1bd9c552f547d0; xes_rfh=RNRaKbivpsex8pvrlsiDzVhg8Z6ztVyE3_zOvqIltS9lycQmNgPXVYVMN5-ulTFQEYrvhZ7TjTep7kHxVHCEJaEXJ52ax4CrUu2pFspnK95lI8sOiOXppswgxOEqE0r9srrv6wryzpI83bar5fLPlmTSUOhNKbnCj8kUkc-AShk.cv0; is_login=1; stu_id=2474364; stu_name=2474364; tfstk=fFp-wYbFqmEJl2rYMWGc-WXUyhimspKyrU-_KwbuOELvfhzlOJAuR9Lv769lE3YvAe_AKavkZBEyHFe3E4lyAJBhdV0iIAxz49WISY4njsEPxMs7NybIhSNitP0IIAxyV3eFo_kMEtqLFNbCd_1Bcr_VYu6CAJiAlMIaOzTBRniAvGaQRasShosCV9_BR9ivcfK03wlCSJd3agEIn-wbpJpAc27k2cwhDLSRwNtWDJwQfgCR53_x7y5zV6LRwKD87gdXXUjJ8AyPF6dW1T9KWYBXbIY5DegT9ZO9UpCMeVFNPL7eWTOxl8BCFLdG_9hT4ivJcd5pU4efyE-XsTJsuJL6mhvPgp3TlwRlbtsJMDNfP6sz5dvOnL4GWMVSDmFUT_sqnBawBgOxnFIASmY7TW5Y_iQiDbPUT_sVDNm0JWPFM55..; tal_token=tal173Z6lA58dUrXrp5FgPHUoySgBElY7m1BlfarOPHDmXaRDwV5H5mtuNkTgho2zOP_K_qno44pFdzOqbI6ZyxsxO47-klgg-6YLHtU-qJyruRtZnAIOZaDms4rTpGF6PHCr_H37xqxwCKuCm4DafnlIVTRraC5XrxtMJm7lI6474tMgmkzz0j2_LMuzQiScAsAX2kfRtD1-IAko6446jlNlcxTEwCLOLax5ziKAoe-EcTp27vjk-_vTMLfu1zKgO6yKlcsJjkWfqBywKSoq2hyLfqX3S1pXhtM7Sim8s3JOuaYE7c' \
--header 'User-Agent: Apifox/1.0.0 (https://apifox.com)' \
--header 'Accept: */*' \
--header 'Host: localhost:80' \
--header 'Connection: keep-alive' \
--header 'ContentType: text/event-stream'


curl --location --request POST 'http://tabtest.xue.xiwang.com/alg-server/tab/get_chat' \
--header "Content-Type: application/json" \
-d '{
    "session_id": "1122",
    "messages" : "你好",
    "is_init": true,
    "is_refresh" : false
}'



curl --location --request GET 'http://10.74.7.229:80/v1/api/ai/refresh' \
--header 'Cookie: wx=df9813f23a8bd4fd943f98c073bd2055mymyxyxbbq; xesId=eb4db07dd4b0ce9b17c7c0c390cce42c; prelogid=9e6c0d367902d54e3c6889f0f0e05bc9; tal_token=tal173aLsCFlymxX1jSfZsD6fQplbjyuDXR1EyZN7qeam9-uwp25o1unkK0_TsWcNys14g_4FJs4WTC4IzECZBsVYaMvjgBRuGRkzKrspFKbzlW7penyRauAAjqlFG9MkhGeYztwmuFPKJ4ZNyDhfUxuy4T0cH4n2419gYEgKvK-emQ18mkI2y3C4JPl4OM3N4GlmyX1TCVrD-XiDbZtNwu_RuNPTFOIpL9Zv0CEXmq4EpQ8W2pJzr5VeGxByg2pSwHSbpauMQAzIQSzaJW3vs_XqKtRPMUM-DMCt0avUrTB8fdIPjg; tal_token=tal173V3bcvzaw3i0QVnYADbwD-tFXblX7YLt6UI0y8Wfq3MeY13Umfluzr7mYAzRlzBMQ1yjROWWkxUOsV1r8CFLJHde8Ykww93ZDam3P4xAHlQqsz59uYtyTpKRO6FPrXCxpKI_XchP7zlzUWqqjjpaHGjwUD8UGeTS11g8BwOqvRoomkI2y3C4JPl4OM3N4GlmyX1TCVrD-XiDbZtNwu_RuNPTFOIpL9Zv0CEXmq4EpQ8W2pJzr5VeGxByg2pSwHSbpauMQAzIQSzaJW3vs_XqKtRPMUM-DMCt0avUrTB8fdIPjg' \
--header 'User-Agent: Apifox/1.0.0 (https://apifox.com)' \
--header 'Accept: */*' \
--header 'Host: localhost:80' \
--header 'Connection: keep-alive' \
--header 'ContentType: text/event-stream'


curl --location --request POST 'http://10.74.7.229:80/v1/api/ai/chat' \
--header 'Cookie: wx=df9813f23a8bd4fd943f98c073bd2055mymyxyxbbq; xesId=eb4db07dd4b0ce9b17c7c0c390cce42c; prelogid=9e6c0d367902d54e3c6889f0f0e05bc9; tal_token=tal173aLsCFlymxX1jSfZsD6fQplbjyuDXR1EyZN7qeam9-uwp25o1unkK0_TsWcNys14g_4FJs4WTC4IzECZBsVYaMvjgBRuGRkzKrspFKbzlW7penyRauAAjqlFG9MkhGeYztwmuFPKJ4ZNyDhfUxuy4T0cH4n2419gYEgKvK-emQ18mkI2y3C4JPl4OM3N4GlmyX1TCVrD-XiDbZtNwu_RuNPTFOIpL9Zv0CEXmq4EpQ8W2pJzr5VeGxByg2pSwHSbpauMQAzIQSzaJW3vs_XqKtRPMUM-DMCt0avUrTB8fdIPjg' \
--header 'Content-Type: application/json' \
--data-raw '{
    "session_id": "1b7b97d5b71d42129fca297573ae9a71",
    "is_init": false,
    "messages": "简要说一下依赖注入"
}'