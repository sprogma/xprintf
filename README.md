# --- result of run ---


---- gathering cpu information ----
min loop overhead: 31



 --------------------------------------- general ----------------------------------------
    some string with diffrent values
---- testing function xsprintf
 cpu secs:
   avg call time:                45.6368 ns
   avg calls/second:             21.9 m. calls
 cpu clocks:
-  min:              135         (raw        166     )
-  med50:            146         (raw        177     )
-  med90:            150         (raw        181     )
~  mean:             149.962     (raw        180.962 )
~  mean/med:         102.7%      (raw        102.2%  )
~  min/med:          108.1%      (raw        106.6%  )
~  dev:        2.342e+05         (raw  2.342e+05     )
  test details: time: 1500080988 ns, 32870000 cycles;  clocks: 2447382710 (2953302710 raw) sum, 16320000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:               135.4504 ns
   avg calls/second:              7.4 m. calls
 cpu clocks:
-  min:              298         (raw        329     )
-  med50:            337         (raw        368     )
-  med90:            381         (raw        412     )
~  mean:             357.062     (raw        388.062 )
~  mean/med:         106.0%      (raw        105.5%  )
~  min/med:          113.1%      (raw        111.9%  )
~  dev:        2.124e+06         (raw  2.124e+06     )
  test details: time: 1500790145 ns, 11080000 cycles;  clocks: 3067161733 (3333451733 raw) sum, 8590000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:               109.6926 ns
   avg calls/second:              9.1 m. calls
 cpu clocks:
-  min:              229         (raw        260     )
-  med50:            257         (raw        288     )
-  med90:            272         (raw        303     )
~  mean:             263.381     (raw        294.381 )
~  mean/med:         102.5%      (raw        102.2%  )
~  min/med:          112.2%      (raw        110.8%  )
~  dev:        8.917e+05         (raw  8.917e+05     )
  test details: time: 1500595246 ns, 13680000 cycles;  clocks: 2886657514 (3226417514 raw) sum, 10960000 cycles



 --------------------------------------- empty call ----------------------------------------
    tests call with empty format buffer
---- testing function xsprintf
 cpu secs:
   avg call time:                 1.4469 ns
   avg calls/second:            691.1 m. calls
 cpu clocks:
-  min:                4         (raw         35     )
-  med50:             10         (raw         41     )
-  med90:             12         (raw         43     )
~  mean:              10.587     (raw         41.587 )
~  mean/med:         105.9%      (raw        101.4%  )
~  min/med:          250.0%      (raw        117.1%  )
~  dev:        1.103e+05         (raw  1.103e+05     )
  test details: time: 144678933 ns, 99990000 cycles;  clocks: 153617835 (603427835 raw) sum, 14510000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:                 9.0831 ns
   avg calls/second:            110.1 m. calls
 cpu clocks:
-  min:               26         (raw         57     )
-  med50:             34         (raw         65     )
-  med90:             54         (raw         85     )
~  mean:              41.757     (raw         72.757 )
~  mean/med:         122.8%      (raw        111.9%  )
~  min/med:          130.8%      (raw        114.0%  )
~  dev:        8.309e+06         (raw  8.309e+06     )
  test details: time: 500025661 ns, 55050000 cycles;  clocks: 416731232 (726111232 raw) sum, 9980000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:                 3.9812 ns
   avg calls/second:            251.2 m. calls
 cpu clocks:
-  min:               14         (raw         45     )
-  med50:             18         (raw         49     )
-  med90:             20         (raw         51     )
~  mean:              18.407     (raw         49.407 )
~  mean/med:         102.3%      (raw        100.8%  )
~  min/med:          128.6%      (raw        108.9%  )
~  dev:        7.837e+04         (raw  7.837e+04     )
  test details: time: 398084536 ns, 99990000 cycles;  clocks: 244812817 (657112817 raw) sum, 13300000 cycles



 --------------------------------------- medium parts ----------------------------------------
    tests string with mixed %c and long text parts
---- testing function xsprintf
 cpu secs:
   avg call time:                23.3734 ns
   avg calls/second:             42.8 m. calls
 cpu clocks:
-  min:               63         (raw         94     )
-  med50:             75         (raw        106     )
-  med90:             86         (raw        117     )
~  mean:              82.827     (raw        113.827 )
~  mean/med:         110.4%      (raw        107.4%  )
~  min/med:          119.0%      (raw        112.8%  )
~  dev:        1.382e+05         (raw  1.382e+05     )
  test details: time: 1000148059 ns, 42790000 cycles;  clocks: 1257314031 (1727894031 raw) sum, 15180000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:                44.0865 ns
   avg calls/second:             22.7 m. calls
 cpu clocks:
-  min:              101         (raw        132     )
-  med50:            111         (raw        142     )
-  med90:            124         (raw        155     )
~  mean:             119.465     (raw        150.465 )
~  mean/med:         107.6%      (raw        106.0%  )
~  min/med:          109.9%      (raw        107.6%  )
~  dev:        3.402e+07         (raw  3.402e+07     )
  test details: time: 1000322007 ns, 22690000 cycles;  clocks: 1530347856 (1927457856 raw) sum, 12810000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:                58.5289 ns
   avg calls/second:             17.1 m. calls
 cpu clocks:
-  min:              117         (raw        148     )
-  med50:            131         (raw        162     )
-  med90:            144         (raw        175     )
~  mean:             137.157     (raw        168.157 )
~  mean/med:         104.7%      (raw        103.8%  )
~  min/med:          112.0%      (raw        109.5%  )
~  dev:        2.621e+05         (raw  2.621e+05     )
  test details: time: 1000259591 ns, 17090000 cycles;  clocks: 1599253382 (1960713382 raw) sum, 11660000 cycles



 --------------------------------------- long parts ----------------------------------------
    tests string with mixed %c and long text parts
---- testing function xsprintf
 cpu secs:
   avg call time:               248.5522 ns
   avg calls/second:              4.0 m. calls
 cpu clocks:
-  min:              572         (raw        603     )
-  med50:            592         (raw        623     )
-  med90:            806         (raw        837     )
~  mean:             680.716     (raw        711.716 )
~  mean/med:         115.0%      (raw        114.2%  )
~  min/med:          103.5%      (raw        103.3%  )
~  dev:        8.442e+07         (raw  8.442e+07     )
  test details: time: 1250217777 ns, 5030000 cycles;  clocks: 2797740772 (2925150772 raw) sum, 4110000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:               275.3827 ns
   avg calls/second:              3.6 m. calls
 cpu clocks:
-  min:              617         (raw        648     )
-  med50:            654         (raw        685     )
-  med90:            722         (raw        753     )
~  mean:             701.103     (raw        732.103 )
~  mean/med:         107.2%      (raw        106.9%  )
~  min/med:          106.0%      (raw        105.7%  )
~  dev:        1.395e+07         (raw  1.395e+07     )
  test details: time: 1252991334 ns, 4550000 cycles;  clocks: 2818432812 (2943052812 raw) sum, 4020000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:              1806.0552 ns
   avg calls/second:              0.6 m. calls
 cpu clocks:
-  min:             3985         (raw       4016     )
-  med50:           4057         (raw       4088     )
-  med90:           4580         (raw       4611     )
~  mean:            4463.370     (raw       4494.370 )
~  mean/med:         110.0%      (raw        109.9%  )
~  min/med:          101.8%      (raw        101.8%  )
~  dev:        1.128e+07         (raw  1.128e+07     )
  test details: time: 1264238619 ns, 700000 cycles;  clocks: 3079725164 (3101115164 raw) sum, 690000 cycles



 --------------------------------------- group parsing ----------------------------------------
    tests many subsequent %c
---- testing function xsprintf
 cpu secs:
   avg call time:               113.6074 ns
   avg calls/second:              8.8 m. calls
 cpu clocks:
-  min:              259         (raw        290     )
-  med50:            269         (raw        300     )
-  med90:            274         (raw        305     )
~  mean:             280.639     (raw        311.639 )
~  mean/med:         104.3%      (raw        103.9%  )
~  min/med:          103.9%      (raw        103.4%  )
~  dev:        7.428e+05         (raw  7.428e+05     )
  test details: time: 1500754046 ns, 13210000 cycles;  clocks: 2921456008 (3244166008 raw) sum, 10410000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:               276.8008 ns
   avg calls/second:              3.6 m. calls
 cpu clocks:
-  min:              623         (raw        654     )
-  med50:            643         (raw        674     )
-  med90:            727         (raw        758     )
~  mean:             700.553     (raw        731.553 )
~  mean/med:         109.0%      (raw        108.5%  )
~  min/med:          103.2%      (raw        103.1%  )
~  dev:        2.939e+06         (raw  2.939e+06     )
  test details: time: 1500260331 ns, 5420000 cycles;  clocks: 3369661716 (3518771716 raw) sum, 4810000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:               334.8939 ns
   avg calls/second:              3.0 m. calls
 cpu clocks:
-  min:              661         (raw        692     )
-  med50:            798         (raw        829     )
-  med90:            893         (raw        924     )
~  mean:             851.199     (raw        882.199 )
~  mean/med:         106.7%      (raw        106.4%  )
~  min/med:          120.7%      (raw        119.8%  )
~  dev:        3.324e+07         (raw  3.324e+07     )
  test details: time: 1500324882 ns, 4480000 cycles;  clocks: 3438842048 (3564082048 raw) sum, 4040000 cycles



 --------------------------------------- bad groups ----------------------------------------
    tests many %c with 1 digit between them
---- testing function xsprintf
 cpu secs:
   avg call time:               287.5826 ns
   avg calls/second:              3.5 m. calls
 cpu clocks:
-  min:              652         (raw        683     )
-  med50:            674         (raw        705     )
-  med90:            727         (raw        758     )
~  mean:             700.353     (raw        731.353 )
~  mean/med:         103.9%      (raw        103.7%  )
~  min/med:          103.4%      (raw        103.2%  )
~  dev:        1.544e+06         (raw  1.544e+06     )
  test details: time: 1501181199 ns, 5220000 cycles;  clocks: 3375703447 (3525123447 raw) sum, 4820000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:               376.5165 ns
   avg calls/second:              2.7 m. calls
 cpu clocks:
-  min:              759         (raw        790     )
-  med50:            867         (raw        898     )
-  med90:           1074         (raw       1105     )
~  mean:             971.472     (raw       1002.472 )
~  mean/med:         112.0%      (raw        111.6%  )
~  min/med:          114.2%      (raw        113.7%  )
~  dev:        2.791e+07         (raw  2.791e+07     )
  test details: time: 1502300794 ns, 3990000 cycles;  clocks: 3468154141 (3578824141 raw) sum, 3570000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:               423.3759 ns
   avg calls/second:              2.4 m. calls
 cpu clocks:
-  min:              824         (raw        855     )
-  med50:           1003         (raw       1034     )
-  med90:           1277         (raw       1308     )
~  mean:            1101.474     (raw       1132.474 )
~  mean/med:         109.8%      (raw        109.5%  )
~  min/med:          121.7%      (raw        120.9%  )
~  dev:        1.625e+07         (raw  1.625e+07     )
  test details: time: 1502984324 ns, 3550000 cycles;  clocks: 3491671030 (3589941030 raw) sum, 3170000 cycles



 --------------------------------------- variable width ----------------------------------------
    tests many little paddings at %c
---- testing function xsprintf
 cpu secs:
   avg call time:               112.2862 ns
   avg calls/second:              8.9 m. calls
 cpu clocks:
-  min:              239         (raw        270     )
-  med50:            290         (raw        321     )
-  med90:            394         (raw        425     )
~  mean:             332.948     (raw        363.948 )
~  mean/med:         114.8%      (raw        113.4%  )
~  min/med:          121.3%      (raw        118.9%  )
~  dev:        1.034e+07         (raw  1.034e+07     )
  test details: time: 1000469886 ns, 8910000 cycles;  clocks: 1997689954 (2183689954 raw) sum, 6000000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:               409.6960 ns
   avg calls/second:              2.4 m. calls
 cpu clocks:
-  min:              672         (raw        703     )
-  med50:            849         (raw        880     )
-  med90:           1109         (raw       1140     )
~  mean:             958.486     (raw        989.486 )
~  mean/med:         112.9%      (raw        112.4%  )
~  min/med:          126.3%      (raw        125.2%  )
~  dev:        9.289e+07         (raw  9.289e+07     )
  test details: time: 1003755235 ns, 2450000 cycles;  clocks: 2319535138 (2394555138 raw) sum, 2420000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:               428.0445 ns
   avg calls/second:              2.3 m. calls
 cpu clocks:
-  min:              904         (raw        935     )
-  med50:           1025         (raw       1056     )
-  med90:           1139         (raw       1170     )
~  mean:            1111.907     (raw       1142.907 )
~  mean/med:         108.5%      (raw        108.2%  )
~  min/med:          113.4%      (raw        112.9%  )
~  dev:        5.551e+06         (raw  5.551e+06     )
  test details: time: 1001624103 ns, 2340000 cycles;  clocks: 2335004382 (2400104382 raw) sum, 2100000 cycles



 --------------------------------------- little space ----------------------------------------
    tests many little paddings at %c
---- testing function xsprintf
 cpu secs:
   avg call time:               117.3188 ns
   avg calls/second:              8.5 m. calls
 cpu clocks:
-  min:              267         (raw        298     )
-  med50:            280         (raw        311     )
-  med90:            319         (raw        350     )
~  mean:             293.393     (raw        324.393 )
~  mean/med:         104.8%      (raw        104.3%  )
~  min/med:          104.9%      (raw        104.4%  )
~  dev:        4.416e+05         (raw  4.416e+05     )
  test details: time: 1000729182 ns, 8530000 cycles;  clocks: 1974531936 (2183161936 raw) sum, 6730000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:               351.0408 ns
   avg calls/second:              2.8 m. calls
 cpu clocks:
-  min:              714         (raw        745     )
-  med50:            870         (raw        901     )
-  med90:            986         (raw       1017     )
~  mean:             930.292     (raw        961.292 )
~  mean/med:         106.9%      (raw        106.7%  )
~  min/med:          121.8%      (raw        120.9%  )
~  dev:        1.194e+08         (raw  1.194e+08     )
  test details: time: 1000466180 ns, 2850000 cycles;  clocks: 2316427035 (2393617035 raw) sum, 2490000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:               470.3221 ns
   avg calls/second:              2.1 m. calls
 cpu clocks:
-  min:              946         (raw        977     )
-  med50:           1057         (raw       1088     )
-  med90:           1495         (raw       1526     )
~  mean:            1210.945     (raw       1241.945 )
~  mean/med:         114.6%      (raw        114.1%  )
~  min/med:          111.7%      (raw        111.4%  )
~  dev:        2.259e+06         (raw  2.259e+06     )
  test details: time: 1001786090 ns, 2130000 cycles;  clocks: 2337124468 (2396954468 raw) sum, 1930000 cycles



 --------------------------------------- large space ----------------------------------------
    tests very big padding at %c
---- testing function xsprintf
 cpu secs:
   avg call time:                93.4039 ns
   avg calls/second:             10.7 m. calls
 cpu clocks:
-  min:              200         (raw        231     )
-  med50:            221         (raw        252     )
-  med90:            237         (raw        268     )
~  mean:             229.482     (raw        260.482 )
~  mean/med:         103.8%      (raw        103.4%  )
~  min/med:          110.5%      (raw        109.1%  )
~  dev:        8.936e+05         (raw  8.936e+05     )
  test details: time: 1000355282 ns, 10710000 cycles;  clocks: 1858804808 (2109904808 raw) sum, 8100000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:                99.3477 ns
   avg calls/second:             10.1 m. calls
 cpu clocks:
-  min:              245         (raw        276     )
-  med50:            251         (raw        282     )
-  med90:            284         (raw        315     )
~  mean:             276.560     (raw        307.560 )
~  mean/med:         110.2%      (raw        109.1%  )
~  min/med:          102.4%      (raw        102.2%  )
~  dev:        1.397e+08         (raw  1.397e+08     )
  test details: time: 1000431630 ns, 10070000 cycles;  clocks: 1969105681 (2189825681 raw) sum, 7120000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:                87.7983 ns
   avg calls/second:             11.4 m. calls
 cpu clocks:
-  min:              227         (raw        258     )
-  med50:            233         (raw        264     )
-  med90:            259         (raw        290     )
~  mean:             255.850     (raw        286.850 )
~  mean/med:         109.8%      (raw        108.7%  )
~  min/med:          102.6%      (raw        102.3%  )
~  dev:        2.019e+05         (raw  2.019e+05     )
  test details: time: 1000022525 ns, 11390000 cycles;  clocks: 1908643698 (2139903698 raw) sum, 7460000 cycles



 --------------------------------------- large zero ----------------------------------------
    tests very big padding by zeroes at %c
---- testing function xsprintf
 cpu secs:
   avg call time:                92.9319 ns
   avg calls/second:             10.8 m. calls
 cpu clocks:
-  min:              200         (raw        231     )
-  med50:            222         (raw        253     )
-  med90:            265         (raw        296     )
~  mean:             239.559     (raw        270.559 )
~  mean/med:         107.9%      (raw        106.9%  )
~  min/med:          111.0%      (raw        109.5%  )
~  dev:        2.300e+07         (raw  2.300e+07     )
  test details: time: 1000876663 ns, 10770000 cycles;  clocks: 1897306140 (2142826140 raw) sum, 7920000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:                95.6321 ns
   avg calls/second:             10.5 m. calls
 cpu clocks:
-  min:              245         (raw        276     )
-  med50:            251         (raw        282     )
-  med90:            278         (raw        309     )
~  mean:             269.193     (raw        300.193 )
~  mean/med:         107.2%      (raw        106.5%  )
~  min/med:          102.4%      (raw        102.2%  )
~  dev:        3.622e+07         (raw  3.622e+07     )
  test details: time: 1000311518 ns, 10460000 cycles;  clocks: 1951651914 (2176401914 raw) sum, 7250000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:                88.8674 ns
   avg calls/second:             11.3 m. calls
 cpu clocks:
-  min:              227         (raw        258     )
-  med50:            233         (raw        264     )
-  med90:            235         (raw        266     )
~  mean:             251.721     (raw        282.721 )
~  mean/med:         108.0%      (raw        107.1%  )
~  min/med:          102.6%      (raw        102.3%  )
~  dev:        2.305e+07         (raw  2.305e+07     )
  test details: time: 1000647234 ns, 11260000 cycles;  clocks: 1915594417 (2151504417 raw) sum, 7610000 cycles



 --------------------------------------- little -padd ----------------------------------------
    tests many small negative paddings at %c
---- testing function xsprintf
 cpu secs:
   avg call time:               137.9555 ns
   avg calls/second:              7.2 m. calls
 cpu clocks:
-  min:              310         (raw        341     )
-  med50:            337         (raw        368     )
-  med90:            341         (raw        372     )
~  mean:             361.224     (raw        392.224 )
~  mean/med:         107.2%      (raw        106.6%  )
~  min/med:          108.7%      (raw        107.9%  )
~  dev:        2.633e+07         (raw  2.633e+07     )
  test details: time: 1001556996 ns, 7260000 cycles;  clocks: 2069814503 (2247444503 raw) sum, 5730000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:               363.1457 ns
   avg calls/second:              2.8 m. calls
 cpu clocks:
-  min:              761         (raw        792     )
-  med50:            822         (raw        853     )
-  med90:            871         (raw        902     )
~  mean:             871.610     (raw        902.610 )
~  mean/med:         106.0%      (raw        105.8%  )
~  min/med:          108.0%      (raw        107.7%  )
~  dev:        5.094e+07         (raw  5.094e+07     )
  test details: time: 1002282127 ns, 2760000 cycles;  clocks: 2309767458 (2391917458 raw) sum, 2650000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:               500.9835 ns
   avg calls/second:              2.0 m. calls
 cpu clocks:
-  min:             1009         (raw       1040     )
-  med50:           1159         (raw       1190     )
-  med90:           1884         (raw       1915     )
~  mean:            1370.905     (raw       1401.905 )
~  mean/med:         118.3%      (raw        117.8%  )
~  min/med:          114.9%      (raw        114.4%  )
~  dev:        2.153e+07         (raw  2.153e+07     )
  test details: time: 1001966985 ns, 2000000 cycles;  clocks: 2357957186 (2411277186 raw) sum, 1720000 cycles



 --------------------------------------- large -padd ----------------------------------------
    tests very big negative padding at %c
---- testing function xsprintf
 cpu secs:
   avg call time:                96.2287 ns
   avg calls/second:             10.4 m. calls
 cpu clocks:
-  min:              201         (raw        232     )
-  med50:            221         (raw        252     )
-  med90:            258         (raw        289     )
~  mean:             237.855     (raw        268.855 )
~  mean/med:         107.6%      (raw        106.7%  )
~  min/med:          110.0%      (raw        108.6%  )
~  dev:        3.269e+05         (raw  3.269e+05     )
  test details: time: 1000778862 ns, 10400000 cycles;  clocks: 1869539801 (2113199801 raw) sum, 7860000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:               105.7669 ns
   avg calls/second:              9.5 m. calls
 cpu clocks:
-  min:              242         (raw        273     )
-  med50:            249         (raw        280     )
-  med90:            353         (raw        384     )
~  mean:             306.047     (raw        337.047 )
~  mean/med:         122.9%      (raw        120.4%  )
~  min/med:          102.9%      (raw        102.6%  )
~  dev:        3.730e+07         (raw  3.730e+07     )
  test details: time: 1000554692 ns, 9460000 cycles;  clocks: 1970940165 (2170580165 raw) sum, 6440000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:                90.2714 ns
   avg calls/second:             11.1 m. calls
 cpu clocks:
-  min:              231         (raw        262     )
-  med50:            239         (raw        270     )
-  med90:            265         (raw        296     )
~  mean:             254.708     (raw        285.708 )
~  mean/med:         106.6%      (raw        105.8%  )
~  min/med:          103.5%      (raw        103.1%  )
~  dev:        1.900e+07         (raw  1.900e+07     )
  test details: time: 1000206983 ns, 11080000 cycles;  clocks: 1923044360 (2157094360 raw) sum, 7550000 cycles



 --------------------------------------- empty string-1 ----------------------------------------
    tests %.s variant
---- testing function xsprintf
 cpu secs:
   avg call time:                 6.4106 ns
   avg calls/second:            156.0 m. calls
 cpu clocks:
-  min:               26         (raw         57     )
-  med50:             32         (raw         63     )
-  med90:             38         (raw         69     )
~  mean:              35.992     (raw         66.992 )
~  mean/med:         112.5%      (raw        106.3%  )
~  min/med:          123.1%      (raw        110.5%  )
~  dev:        4.381e+04         (raw  4.381e+04     )
  test details: time: 500024262 ns, 78000000 cycles;  clocks: 394833293 (734903293 raw) sum, 10970000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:                16.8435 ns
   avg calls/second:             59.4 m. calls
 cpu clocks:
-  min:               42         (raw         73     )
-  med50:             46         (raw         77     )
-  med90:             48         (raw         79     )
~  mean:              49.778     (raw         80.778 )
~  mean/med:         108.2%      (raw        104.9%  )
~  min/med:          109.5%      (raw        105.5%  )
~  dev:        1.663e+07         (raw  1.663e+07     )
  test details: time: 500084514 ns, 29690000 cycles;  clocks: 483342168 (784352168 raw) sum, 9710000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:                11.5807 ns
   avg calls/second:             86.4 m. calls
 cpu clocks:
-  min:               24         (raw         55     )
-  med50:             30         (raw         61     )
-  med90:             32         (raw         63     )
~  mean:              30.286     (raw         61.286 )
~  mean/med:         101.0%      (raw        100.5%  )
~  min/med:          125.0%      (raw        110.9%  )
~  dev:        1.591e+04         (raw  1.591e+04     )
  test details: time: 500056172 ns, 43180000 cycles;  clocks: 357678094 (723788094 raw) sum, 11810000 cycles



 --------------------------------------- empty string-2 ----------------------------------------
    tests %.*s variant
---- testing function xsprintf
 cpu secs:
   avg call time:                 8.3964 ns
   avg calls/second:            119.1 m. calls
 cpu clocks:
-  min:               28         (raw         59     )
-  med50:             38         (raw         69     )
-  med90:             58         (raw         89     )
~  mean:              46.640     (raw         77.640 )
~  mean/med:         122.7%      (raw        112.5%  )
~  min/med:          135.7%      (raw        116.9%  )
~  dev:        1.886e+06         (raw  1.886e+06     )
  test details: time: 500007983 ns, 59550000 cycles;  clocks: 433288305 (721278305 raw) sum, 9290000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:                15.7587 ns
   avg calls/second:             63.5 m. calls
 cpu clocks:
-  min:               42         (raw         73     )
-  med50:             48         (raw         79     )
-  med90:             51         (raw         82     )
~  mean:              50.724     (raw         81.724 )
~  mean/med:         105.7%      (raw        103.4%  )
~  min/med:          114.3%      (raw        108.2%  )
~  dev:        3.892e+04         (raw  3.892e+04     )
  test details: time: 500022749 ns, 31730000 cycles;  clocks: 498106664 (802526664 raw) sum, 9820000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:                12.0186 ns
   avg calls/second:             83.2 m. calls
 cpu clocks:
-  min:               24         (raw         55     )
-  med50:             30         (raw         61     )
-  med90:             53         (raw         84     )
~  mean:              36.814     (raw         67.814 )
~  mean/med:         122.7%      (raw        111.2%  )
~  min/med:          125.0%      (raw        110.9%  )
~  dev:        4.952e+04         (raw  4.952e+04     )
  test details: time: 500092780 ns, 41610000 cycles;  clocks: 385808913 (710688913 raw) sum, 10480000 cycles



 --------------------------------------- empty string-3 ----------------------------------------
    tests %s + "" variant
---- testing function xsprintf
 cpu secs:
   avg call time:                 6.8675 ns
   avg calls/second:            145.6 m. calls
 cpu clocks:
-  min:               28         (raw         59     )
-  med50:             36         (raw         67     )
-  med90:             62         (raw         93     )
~  mean:              42.737     (raw         73.737 )
~  mean/med:         118.7%      (raw        110.1%  )
~  min/med:          128.6%      (raw        113.6%  )
~  dev:        8.780e+04         (raw  8.780e+04     )
  test details: time: 500022690 ns, 72810000 cycles;  clocks: 432495221 (746215221 raw) sum, 10120000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:                16.4345 ns
   avg calls/second:             60.8 m. calls
 cpu clocks:
-  min:               45         (raw         76     )
-  med50:             51         (raw         82     )
-  med90:             54         (raw         85     )
~  mean:              53.562     (raw         84.562 )
~  mean/med:         105.0%      (raw        103.1%  )
~  min/med:          113.3%      (raw        107.9%  )
~  dev:        1.074e+05         (raw  1.074e+05     )
  test details: time: 500102607 ns, 30430000 cycles;  clocks: 508840410 (803340410 raw) sum, 9500000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:                12.2163 ns
   avg calls/second:             81.9 m. calls
 cpu clocks:
-  min:               24         (raw         55     )
-  med50:             30         (raw         61     )
-  med90:             34         (raw         65     )
~  mean:              31.804     (raw         62.804 )
~  mean/med:         106.0%      (raw        103.0%  )
~  min/med:          125.0%      (raw        110.9%  )
~  dev:        4.717e+04         (raw  4.717e+04     )
  test details: time: 500014343 ns, 40930000 cycles;  clocks: 365741745 (722241745 raw) sum, 11500000 cycles



 --------------------------------------- medium string ----------------------------------------
    tests 3-4 of 50-70 character strings
---- testing function xsprintf
 cpu secs:
   avg call time:                15.3055 ns
   avg calls/second:             65.3 m. calls
 cpu clocks:
-  min:               51         (raw         82     )
-  med50:             59         (raw         90     )
-  med90:             69         (raw        100     )
~  mean:              65.174     (raw         96.174 )
~  mean/med:         110.5%      (raw        106.9%  )
~  min/med:          115.7%      (raw        109.8%  )
~  dev:        1.511e+06         (raw  1.511e+06     )
  test details: time: 750124175 ns, 49010000 cycles;  clocks: 830971568 (1226221568 raw) sum, 12750000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:                38.2527 ns
   avg calls/second:             26.1 m. calls
 cpu clocks:
-  min:               91         (raw        122     )
-  med50:             99         (raw        130     )
-  med90:            105         (raw        136     )
~  mean:             104.403     (raw        135.403 )
~  mean/med:         105.5%      (raw        104.2%  )
~  min/med:          108.8%      (raw        106.6%  )
~  dev:        6.474e+04         (raw  6.474e+04     )
  test details: time: 750134904 ns, 19610000 cycles;  clocks: 1080576135 (1401426135 raw) sum, 10350000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:                63.8897 ns
   avg calls/second:             15.7 m. calls
 cpu clocks:
-  min:              138         (raw        169     )
-  med50:            146         (raw        177     )
-  med90:            162         (raw        193     )
~  mean:             151.182     (raw        182.182 )
~  mean/med:         103.5%      (raw        102.9%  )
~  min/med:          105.8%      (raw        104.7%  )
~  dev:        8.570e+04         (raw  8.570e+04     )
  test details: time: 750065644 ns, 11740000 cycles;  clocks: 1245739775 (1501179775 raw) sum, 8240000 cycles



 --------------------------------------- large string ----------------------------------------
    tests one large string
---- testing function xsprintf
 cpu secs:
   avg call time:               418.5056 ns
   avg calls/second:              2.4 m. calls
 cpu clocks:
-  min:              824         (raw        855     )
-  med50:            906         (raw        937     )
-  med90:            999         (raw       1030     )
~  mean:             967.422     (raw        998.422 )
~  mean/med:         106.8%      (raw        106.6%  )
~  min/med:          110.0%      (raw        109.6%  )
~  dev:        9.414e+07         (raw  9.414e+07     )
  test details: time: 1000228426 ns, 2390000 cycles;  clocks: 2331486815 (2406196815 raw) sum, 2410000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:               284.2673 ns
   avg calls/second:              3.5 m. calls
 cpu clocks:
-  min:              641         (raw        672     )
-  med50:            682         (raw        713     )
-  med90:            699         (raw        730     )
~  mean:             706.166     (raw        737.166 )
~  mean/med:         103.5%      (raw        103.4%  )
~  min/med:          106.4%      (raw        106.1%  )
~  dev:        1.007e+06         (raw  1.007e+06     )
  test details: time: 1000620835 ns, 3520000 cycles;  clocks: 2252668357 (2351558357 raw) sum, 3190000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:              3246.0725 ns
   avg calls/second:              0.3 m. calls
 cpu clocks:
-  min:             7133         (raw       7164     )
-  med50:           7423         (raw       7454     )
-  med90:           7521         (raw       7552     )
~  mean:            7669.979     (raw       7700.979 )
~  mean/med:         103.3%      (raw        103.3%  )
~  min/med:          104.1%      (raw        104.0%  )
~  dev:        8.236e+06         (raw  8.236e+06     )
  test details: time: 1038743208 ns, 320000 cycles;  clocks: 2531093015 (2541323015 raw) sum, 330000 cycles



 --------------------------------------- small %float ----------------------------------------
    tests one float string
---- testing function xsprintf
 cpu secs:
   avg call time:                47.5948 ns
   avg calls/second:             21.0 m. calls
 cpu clocks:
-  min:              180         (raw        211     )
-  med50:            186         (raw        217     )
-  med90:            188         (raw        219     )
~  mean:             188.904     (raw        219.904 )
~  mean/med:         101.6%      (raw        101.3%  )
~  min/med:          103.3%      (raw        102.8%  )
~  dev:        4.830e+05         (raw  4.830e+05     )
  test details: time: 750093678 ns, 15760000 cycles;  clocks: 1327992479 (1545922479 raw) sum, 7030000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:                60.4153 ns
   avg calls/second:             16.6 m. calls
 cpu clocks:
-  min:              134         (raw        165     )
-  med50:            151         (raw        182     )
-  med90:            247         (raw        278     )
~  mean:             193.855     (raw        224.855 )
~  mean/med:         128.4%      (raw        123.5%  )
~  min/med:          112.7%      (raw        110.3%  )
~  dev:        5.379e+06         (raw  5.379e+06     )
  test details: time: 750357472 ns, 12420000 cycles;  clocks: 1325967068 (1538007068 raw) sum, 6840000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:                32.1539 ns
   avg calls/second:             31.1 m. calls
 cpu clocks:
-  min:               99         (raw        130     )
-  med50:            107         (raw        138     )
-  med90:            109         (raw        140     )
~  mean:             118.245     (raw        149.245 )
~  mean/med:         110.5%      (raw        108.1%  )
~  min/med:          108.1%      (raw        106.2%  )
~  dev:        2.025e+05         (raw  2.025e+05     )
  test details: time: 750149555 ns, 23330000 cycles;  clocks: 1124505945 (1419315945 raw) sum, 9510000 cycles



 --------------------------------------- precise %float ----------------------------------------
    tests one float string
---- testing function xsprintf
 cpu secs:
   avg call time:                48.9063 ns
   avg calls/second:             20.4 m. calls
 cpu clocks:
-  min:              180         (raw        211     )
-  med50:            188         (raw        219     )
-  med90:            209         (raw        240     )
~  mean:             196.834     (raw        227.834 )
~  mean/med:         104.7%      (raw        104.0%  )
~  min/med:          104.4%      (raw        103.8%  )
~  dev:        1.685e+05         (raw  1.685e+05     )
  test details: time: 750221910 ns, 15340000 cycles;  clocks: 1346344265 (1558384265 raw) sum, 6840000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:               355.5005 ns
   avg calls/second:              2.8 m. calls
 cpu clocks:
-  min:              776         (raw        807     )
-  med50:            861         (raw        892     )
-  med90:            899         (raw        930     )
~  mean:             884.101     (raw        915.101 )
~  mean/med:         102.7%      (raw        102.6%  )
~  min/med:          111.0%      (raw        110.5%  )
~  dev:        1.863e+06         (raw  1.863e+06     )
  test details: time: 750105969 ns, 2110000 cycles;  clocks: 1723996473 (1784446473 raw) sum, 1950000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:                43.7585 ns
   avg calls/second:             22.9 m. calls
 cpu clocks:
-  min:              105         (raw        136     )
-  med50:            111         (raw        142     )
-  med90:            113         (raw        144     )
~  mean:             113.072     (raw        144.072 )
~  mean/med:         101.9%      (raw        101.5%  )
~  min/med:          105.7%      (raw        104.4%  )
~  dev:        3.086e+05         (raw  3.086e+05     )
  test details: time: 750021005 ns, 17140000 cycles;  clocks: 1106970619 (1410460619 raw) sum, 9790000 cycles



 --------------------------------------- very %float ----------------------------------------
    tests one float string
---- testing function xsprintf
 cpu secs:
   avg call time:                50.9908 ns
   avg calls/second:             19.6 m. calls
 cpu clocks:
-  min:              182         (raw        213     )
-  med50:            189         (raw        220     )
-  med90:            191         (raw        222     )
~  mean:             194.562     (raw        225.562 )
~  mean/med:         102.9%      (raw        102.5%  )
~  min/med:          103.8%      (raw        103.3%  )
~  dev:        5.348e+05         (raw  5.348e+05     )
  test details: time: 750074548 ns, 14710000 cycles;  clocks: 1340533116 (1554123116 raw) sum, 6890000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:             12870.9626 ns
   avg calls/second:              0.1 m. calls
 cpu clocks:
-  min:            28785         (raw      28816     )
-  med50:          31624         (raw      31655     )
-  med90:          31703         (raw      31734     )
~  mean:           32093.564     (raw      32124.564 )
~  mean/med:         101.5%      (raw        101.5%  )
~  min/med:          109.9%      (raw        109.9%  )
~  dev:        4.551e+07         (raw  4.551e+07     )
  test details: time: 772257753 ns, 60000 cycles;  clocks: 1925613821 (1927473821 raw) sum, 60000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:                62.1854 ns
   avg calls/second:             16.1 m. calls
 cpu clocks:
-  min:              149         (raw        180     )
-  med50:            158         (raw        189     )
-  med90:            162         (raw        193     )
~  mean:             162.633     (raw        193.633 )
~  mean/med:         102.9%      (raw        102.5%  )
~  min/med:          106.0%      (raw        105.0%  )
~  dev:        5.357e+06         (raw  5.357e+06     )
  test details: time: 750578078 ns, 12070000 cycles;  clocks: 1268539882 (1510339882 raw) sum, 7800000 cycles



 --------------------------------------- small %e float ----------------------------------------
    tests %e
---- testing function xsprintf
 cpu secs:
   avg call time:                14.5639 ns
   avg calls/second:             68.7 m. calls
 cpu clocks:
-  min:               68         (raw         99     )
-  med50:             73         (raw        104     )
-  med90:             75         (raw        106     )
~  mean:              74.858     (raw        105.858 )
~  mean/med:         102.5%      (raw        101.8%  )
~  min/med:          107.4%      (raw        105.1%  )
~  dev:        2.058e+05         (raw  2.058e+05     )
  test details: time: 500124007 ns, 34340000 cycles;  clocks: 620571768 (877561768 raw) sum, 8290000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:                58.3948 ns
   avg calls/second:             17.1 m. calls
 cpu clocks:
-  min:              135         (raw        166     )
-  med50:            150         (raw        181     )
-  med90:            237         (raw        268     )
~  mean:             191.476     (raw        222.476 )
~  mean/med:         127.7%      (raw        122.9%  )
~  min/med:          111.1%      (raw        109.0%  )
~  dev:        6.751e+07         (raw  6.751e+07     )
  test details: time: 500443690 ns, 8570000 cycles;  clocks: 886532591 (1030062591 raw) sum, 4630000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:                33.2696 ns
   avg calls/second:             30.1 m. calls
 cpu clocks:
-  min:              101         (raw        132     )
-  med50:            107         (raw        138     )
-  med90:            109         (raw        140     )
~  mean:             108.901     (raw        139.901 )
~  mean/med:         101.8%      (raw        101.4%  )
~  min/med:          105.9%      (raw        104.5%  )
~  dev:        1.289e+05         (raw  1.289e+05     )
  test details: time: 500041718 ns, 15030000 cycles;  clocks: 736173894 (945733894 raw) sum, 6760000 cycles



 --------------------------------------- one digit %e ----------------------------------------
    tests %.0e
---- testing function xsprintf
 cpu secs:
   avg call time:                12.0462 ns
   avg calls/second:             83.0 m. calls
 cpu clocks:
-  min:               58         (raw         89     )
-  med50:             63         (raw         94     )
-  med90:             65         (raw         96     )
~  mean:              64.137     (raw         95.137 )
~  mean/med:         101.8%      (raw        101.2%  )
~  min/med:          108.6%      (raw        105.6%  )
~  dev:        3.505e+04         (raw  3.505e+04     )
  test details: time: 500036795 ns, 41510000 cycles;  clocks: 566325651 (840055651 raw) sum, 8830000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:                45.4161 ns
   avg calls/second:             22.0 m. calls
 cpu clocks:
-  min:              101         (raw        132     )
-  med50:            111         (raw        142     )
-  med90:            140         (raw        171     )
~  mean:             123.207     (raw        154.207 )
~  mean/med:         111.0%      (raw        108.6%  )
~  min/med:          109.9%      (raw        107.6%  )
~  dev:        2.910e+05         (raw  2.910e+05     )
  test details: time: 500031676 ns, 11010000 cycles;  clocks: 766349833 (959169833 raw) sum, 6220000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:                27.4510 ns
   avg calls/second:             36.4 m. calls
 cpu clocks:
-  min:               86         (raw        117     )
-  med50:             93         (raw        124     )
-  med90:            105         (raw        136     )
~  mean:             107.257     (raw        138.257 )
~  mean/med:         115.3%      (raw        111.5%  )
~  min/med:          108.1%      (raw        106.0%  )
~  dev:        1.185e+07         (raw  1.185e+07     )
  test details: time: 500157848 ns, 18220000 cycles;  clocks: 711116394 (916646394 raw) sum, 6630000 cycles



 --------------------------------------- normal %e float ----------------------------------------
    tests %.16e
---- testing function xsprintf
 cpu secs:
   avg call time:                19.0331 ns
   avg calls/second:             52.5 m. calls
 cpu clocks:
-  min:               73         (raw        104     )
-  med50:             79         (raw        110     )
-  med90:             81         (raw        112     )
~  mean:              80.429     (raw        111.429 )
~  mean/med:         101.8%      (raw        101.3%  )
~  min/med:          108.2%      (raw        105.8%  )
~  dev:        3.673e+04         (raw  3.673e+04     )
  test details: time: 500190658 ns, 26280000 cycles;  clocks: 642631472 (890321472 raw) sum, 7990000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:               102.4595 ns
   avg calls/second:              9.8 m. calls
 cpu clocks:
-  min:              204         (raw        235     )
-  med50:            237         (raw        268     )
-  med90:            292         (raw        323     )
~  mean:             260.192     (raw        291.192 )
~  mean/med:         109.8%      (raw        108.7%  )
~  min/med:          116.2%      (raw        114.0%  )
~  dev:        2.570e+05         (raw  2.570e+05     )
  test details: time: 500002428 ns, 4880000 cycles;  clocks: 967915229 (1083235229 raw) sum, 3720000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:                41.5341 ns
   avg calls/second:             24.1 m. calls
 cpu clocks:
-  min:              119         (raw        150     )
-  med50:            127         (raw        158     )
-  med90:            129         (raw        160     )
~  mean:             128.994     (raw        159.994 )
~  mean/med:         101.6%      (raw        101.3%  )
~  min/med:          106.7%      (raw        105.3%  )
~  dev:        1.795e+05         (raw  1.795e+05     )
  test details: time: 500070034 ns, 12040000 cycles;  clocks: 782990607 (971160607 raw) sum, 6070000 cycles



 --------------------------------------- large %e float ----------------------------------------
    tests %.5000e
---- testing function xsprintf
 cpu secs:
   avg call time:                43.7125 ns
   avg calls/second:             22.9 m. calls
 cpu clocks:
-  min:              115         (raw        146     )
-  med50:            137         (raw        168     )
-  med90:            202         (raw        233     )
~  mean:             164.861     (raw        195.861 )
~  mean/med:         120.3%      (raw        116.6%  )
~  min/med:          119.1%      (raw        115.1%  )
~  dev:        8.485e+05         (raw  8.485e+05     )
  test details: time: 500070972 ns, 11440000 cycles;  clocks: 819358853 (973428853 raw) sum, 4970000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:             12896.7349 ns
   avg calls/second:              0.1 m. calls
 cpu clocks:
-  min:            28729         (raw      28760     )
-  med50:          31616         (raw      31647     )
-  med90:          31701         (raw      31732     )
~  mean:           32133.691     (raw      32164.691 )
~  mean/med:         101.6%      (raw        101.6%  )
~  min/med:          110.0%      (raw        110.0%  )
~  dev:        4.196e+07         (raw  4.196e+07     )
  test details: time: 515869396 ns, 40000 cycles;  clocks: 1285347629 (1286587629 raw) sum, 40000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:                59.7041 ns
   avg calls/second:             16.7 m. calls
 cpu clocks:
-  min:              152         (raw        183     )
-  med50:            160         (raw        191     )
-  med90:            164         (raw        195     )
~  mean:             164.999     (raw        195.999 )
~  mean/med:         103.1%      (raw        102.6%  )
~  min/med:          105.3%      (raw        104.4%  )
~  dev:        2.306e+07         (raw  2.306e+07     )
  test details: time: 500320664 ns, 8380000 cycles;  clocks: 861295862 (1023115862 raw) sum, 5220000 cycles



 --------------------------------------- zero %u ----------------------------------------
    zero %u
---- testing function xsprintf
 cpu secs:
   avg call time:                 8.3448 ns
   avg calls/second:            119.8 m. calls
 cpu clocks:
-  min:               34         (raw         65     )
-  med50:             40         (raw         71     )
-  med90:             42         (raw         73     )
~  mean:              40.967     (raw         71.967 )
~  mean/med:         102.4%      (raw        101.4%  )
~  min/med:          117.6%      (raw        109.2%  )
~  dev:        8.144e+04         (raw  8.144e+04     )
  test details: time: 500018121 ns, 59920000 cycles;  clocks: 438755199 (770765199 raw) sum, 10710000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:                20.0681 ns
   avg calls/second:             49.8 m. calls
 cpu clocks:
-  min:               50         (raw         81     )
-  med50:             56         (raw         87     )
-  med90:             63         (raw         94     )
~  mean:              61.549     (raw         92.549 )
~  mean/med:         109.9%      (raw        106.4%  )
~  min/med:          112.0%      (raw        107.4%  )
~  dev:        1.670e+05         (raw  1.670e+05     )
  test details: time: 500095861 ns, 24920000 cycles;  clocks: 544709450 (819059450 raw) sum, 8850000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:                15.7045 ns
   avg calls/second:             63.7 m. calls
 cpu clocks:
-  min:               34         (raw         65     )
-  med50:             38         (raw         69     )
-  med90:             70         (raw        101     )
~  mean:              51.833     (raw         82.833 )
~  mean/med:         136.4%      (raw        120.0%  )
~  min/med:          111.8%      (raw        106.2%  )
~  dev:        2.180e+05         (raw  2.180e+05     )
  test details: time: 500030767 ns, 31840000 cycles;  clocks: 479977402 (767037402 raw) sum, 9260000 cycles



 --------------------------------------- little %u ----------------------------------------
    little %u
---- testing function xsprintf
 cpu secs:
   avg call time:                 9.5728 ns
   avg calls/second:            104.5 m. calls
 cpu clocks:
-  min:               38         (raw         69     )
-  med50:             44         (raw         75     )
-  med90:             74         (raw        105     )
~  mean:              56.708     (raw         87.708 )
~  mean/med:         128.9%      (raw        116.9%  )
~  min/med:          115.8%      (raw        108.7%  )
~  dev:        1.656e+06         (raw  1.656e+06     )
  test details: time: 500080555 ns, 52240000 cycles;  clocks: 500164518 (773584518 raw) sum, 8820000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:                23.3406 ns
   avg calls/second:             42.8 m. calls
 cpu clocks:
-  min:               54         (raw         85     )
-  med50:             61         (raw         92     )
-  med90:            107         (raw        138     )
~  mean:              72.813     (raw        103.813 )
~  mean/med:         119.4%      (raw        112.8%  )
~  min/med:          113.0%      (raw        108.2%  )
~  dev:        5.549e+04         (raw  5.549e+04     )
  test details: time: 500189045 ns, 21430000 cycles;  clocks: 592695494 (845035494 raw) sum, 8140000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:                14.1059 ns
   avg calls/second:             70.9 m. calls
 cpu clocks:
-  min:               36         (raw         67     )
-  med50:             42         (raw         73     )
-  med90:             43         (raw         74     )
~  mean:              42.871     (raw         73.871 )
~  mean/med:         102.1%      (raw        101.2%  )
~  min/med:          116.7%      (raw        109.0%  )
~  dev:        7.871e+04         (raw  7.871e+04     )
  test details: time: 500052942 ns, 35450000 cycles;  clocks: 442862595 (763092595 raw) sum, 10330000 cycles



 --------------------------------------- medium %u ----------------------------------------
    medium %u
---- testing function xsprintf
 cpu secs:
   avg call time:                10.1605 ns
   avg calls/second:             98.4 m. calls
 cpu clocks:
-  min:               47         (raw         78     )
-  med50:             54         (raw         85     )
-  med90:             69         (raw        100     )
~  mean:              62.073     (raw         93.073 )
~  mean/med:         114.9%      (raw        109.5%  )
~  min/med:          114.9%      (raw        109.0%  )
~  dev:        2.052e+05         (raw  2.052e+05     )
  test details: time: 500099105 ns, 49220000 cycles;  clocks: 548723978 (822763978 raw) sum, 8840000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:                25.5313 ns
   avg calls/second:             39.2 m. calls
 cpu clocks:
-  min:               72         (raw        105     )
-  med50:             79         (raw        112     )
-  med90:             90         (raw        123     )
~  mean:              83.424     (raw        116.424 )
~  mean/med:         105.6%      (raw        103.9%  )
~  min/med:          109.7%      (raw        106.7%  )
~  dev:        7.616e+04         (raw  7.616e+04     )
  test details: time: 500157898 ns, 19590000 cycles;  clocks: 634853877 (885983877 raw) sum, 7610000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:                20.0791 ns
   avg calls/second:             49.8 m. calls
 cpu clocks:
-  min:               52         (raw         83     )
-  med50:             58         (raw         89     )
-  med90:             78         (raw        109     )
~  mean:              70.638     (raw        101.638 )
~  mean/med:         121.8%      (raw        114.2%  )
~  min/med:          111.5%      (raw        107.2%  )
~  dev:        9.982e+04         (raw  9.982e+04     )
  test details: time: 500169364 ns, 24910000 cycles;  clocks: 579941028 (834451028 raw) sum, 8210000 cycles



 --------------------------------------- large %u ----------------------------------------
    large %u
---- testing function xsprintf
 cpu secs:
   avg call time:                14.2926 ns
   avg calls/second:             70.0 m. calls
 cpu clocks:
-  min:               65         (raw         96     )
-  med50:             71         (raw        102     )
-  med90:             81         (raw        112     )
~  mean:              76.432     (raw        107.432 )
~  mean/med:         107.7%      (raw        105.3%  )
~  min/med:          109.2%      (raw        106.2%  )
~  dev:        1.969e+05         (raw  1.969e+05     )
  test details: time: 500097610 ns, 34990000 cycles;  clocks: 612986555 (861606555 raw) sum, 8020000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:                36.6323 ns
   avg calls/second:             27.3 m. calls
 cpu clocks:
-  min:              109         (raw        140     )
-  med50:            117         (raw        148     )
-  med90:            120         (raw        151     )
~  mean:             122.527     (raw        153.527 )
~  mean/med:         104.7%      (raw        103.7%  )
~  min/med:          107.3%      (raw        105.7%  )
~  dev:        4.986e+04         (raw  4.986e+04     )
  test details: time: 500763954 ns, 13670000 cycles;  clocks: 768242163 (962612163 raw) sum, 6270000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:                25.3038 ns
   avg calls/second:             39.5 m. calls
 cpu clocks:
-  min:               62         (raw         93     )
-  med50:             68         (raw         99     )
-  med90:             71         (raw        102     )
~  mean:              72.523     (raw        103.523 )
~  mean/med:         106.7%      (raw        104.6%  )
~  min/med:          109.7%      (raw        106.5%  )
~  dev:        5.301e+04         (raw  5.301e+04     )
  test details: time: 500003974 ns, 19760000 cycles;  clocks: 597592463 (853032463 raw) sum, 8240000 cycles



 --------------------------------------- zero %d ----------------------------------------
    zero %d
---- testing function xsprintf
 cpu secs:
   avg call time:                 9.2435 ns
   avg calls/second:            108.2 m. calls
 cpu clocks:
-  min:               36         (raw         67     )
-  med50:             41         (raw         72     )
-  med90:             44         (raw         75     )
~  mean:              42.446     (raw         73.446 )
~  mean/med:         103.5%      (raw        102.0%  )
~  min/med:          113.9%      (raw        107.5%  )
~  dev:        2.324e+05         (raw  2.324e+05     )
  test details: time: 500072380 ns, 54100000 cycles;  clocks: 449080511 (777060511 raw) sum, 10580000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:                21.7655 ns
   avg calls/second:             45.9 m. calls
 cpu clocks:
-  min:               50         (raw         81     )
-  med50:             56         (raw         87     )
-  med90:             60         (raw         91     )
~  mean:              58.658     (raw         89.658 )
~  mean/med:         104.7%      (raw        103.1%  )
~  min/med:          112.0%      (raw        107.4%  )
~  dev:        9.087e+04         (raw  9.087e+04     )
  test details: time: 500172078 ns, 22980000 cycles;  clocks: 536724123 (820374123 raw) sum, 9150000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:                13.2907 ns
   avg calls/second:             75.2 m. calls
 cpu clocks:
-  min:               32         (raw         63     )
-  med50:             38         (raw         69     )
-  med90:             81         (raw        112     )
~  mean:              48.811     (raw         79.811 )
~  mean/med:         128.5%      (raw        115.7%  )
~  min/med:          118.8%      (raw        109.5%  )
~  dev:        5.658e+04         (raw  5.658e+04     )
  test details: time: 500263387 ns, 37640000 cycles;  clocks: 464197262 (759007262 raw) sum, 9510000 cycles



 --------------------------------------- little %d ----------------------------------------
    little %d
---- testing function xsprintf
 cpu secs:
   avg call time:                 9.1081 ns
   avg calls/second:            109.8 m. calls
 cpu clocks:
-  min:               40         (raw         71     )
-  med50:             44         (raw         75     )
-  med90:             52         (raw         83     )
~  mean:              50.001     (raw         81.001 )
~  mean/med:         113.6%      (raw        108.0%  )
~  min/med:          110.0%      (raw        105.6%  )
~  dev:        3.450e+05         (raw  3.450e+05     )
  test details: time: 500034249 ns, 54900000 cycles;  clocks: 475008002 (769508002 raw) sum, 9500000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:                26.7393 ns
   avg calls/second:             37.4 m. calls
 cpu clocks:
-  min:               55         (raw         86     )
-  med50:             61         (raw         92     )
-  med90:             64         (raw         95     )
~  mean:              62.883     (raw         93.883 )
~  mean/med:         103.1%      (raw        102.0%  )
~  min/med:          110.9%      (raw        107.0%  )
~  dev:        3.529e+04         (raw  3.529e+04     )
  test details: time: 500025467 ns, 18700000 cycles;  clocks: 567204500 (846824500 raw) sum, 9020000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:                13.1812 ns
   avg calls/second:             75.9 m. calls
 cpu clocks:
-  min:               34         (raw         65     )
-  med50:             40         (raw         71     )
-  med90:             53         (raw         84     )
~  mean:              46.639     (raw         77.639 )
~  mean/med:         116.6%      (raw        109.4%  )
~  min/med:          117.6%      (raw        109.2%  )
~  dev:        5.986e+04         (raw  5.986e+04     )
  test details: time: 500093706 ns, 37940000 cycles;  clocks: 455198296 (757758296 raw) sum, 9760000 cycles



 --------------------------------------- medium %d ----------------------------------------
    medium %d
---- testing function xsprintf
 cpu secs:
   avg call time:                10.4187 ns
   avg calls/second:             96.0 m. calls
 cpu clocks:
-  min:               50         (raw         81     )
-  med50:             54         (raw         85     )
-  med90:             57         (raw         88     )
~  mean:              56.249     (raw         87.249 )
~  mean/med:         104.2%      (raw        102.6%  )
~  min/med:          108.0%      (raw        104.9%  )
~  dev:        1.931e+04         (raw  1.931e+04     )
  test details: time: 500096036 ns, 48000000 cycles;  clocks: 530992351 (823632351 raw) sum, 9440000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:                24.5168 ns
   avg calls/second:             40.8 m. calls
 cpu clocks:
-  min:               75         (raw        106     )
-  med50:             83         (raw        114     )
-  med90:             91         (raw        122     )
~  mean:              85.195     (raw        116.195 )
~  mean/med:         102.6%      (raw        101.9%  )
~  min/med:          110.7%      (raw        107.5%  )
~  dev:        1.918e+05         (raw  1.918e+05     )
  test details: time: 500142983 ns, 20400000 cycles;  clocks: 653448082 (891218082 raw) sum, 7670000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:                18.6984 ns
   avg calls/second:             53.5 m. calls
 cpu clocks:
-  min:               52         (raw         83     )
-  med50:             57         (raw         88     )
-  med90:             65         (raw         96     )
~  mean:              58.888     (raw         89.888 )
~  mean/med:         103.3%      (raw        102.1%  )
~  min/med:          109.6%      (raw        106.0%  )
~  dev:        2.805e+04         (raw  2.805e+04     )
  test details: time: 500182038 ns, 26750000 cycles;  clocks: 544124602 (830564602 raw) sum, 9240000 cycles



 --------------------------------------- large %d ----------------------------------------
    large %d
---- testing function xsprintf
 cpu secs:
   avg call time:                10.0713 ns
   avg calls/second:             99.3 m. calls
 cpu clocks:
-  min:               40         (raw         71     )
-  med50:             46         (raw         77     )
-  med90:             56         (raw         87     )
~  mean:              51.752     (raw         82.752 )
~  mean/med:         112.5%      (raw        107.5%  )
~  min/med:          115.0%      (raw        108.5%  )
~  dev:        1.033e+06         (raw  1.033e+06     )
  test details: time: 500039235 ns, 49650000 cycles;  clocks: 484397879 (774557879 raw) sum, 9360000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:                22.5564 ns
   avg calls/second:             44.3 m. calls
 cpu clocks:
-  min:               58         (raw         89     )
-  med50:             63         (raw         94     )
-  med90:             74         (raw        105     )
~  mean:              69.856     (raw        100.856 )
~  mean/med:         110.9%      (raw        107.3%  )
~  min/med:          108.6%      (raw        105.6%  )
~  dev:        2.735e+05         (raw  2.735e+05     )
  test details: time: 500075984 ns, 22170000 cycles;  clocks: 593074500 (856264500 raw) sum, 8490000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:                16.2300 ns
   avg calls/second:             61.6 m. calls
 cpu clocks:
-  min:               36         (raw         67     )
-  med50:             42         (raw         73     )
-  med90:             52         (raw         83     )
~  mean:              49.264     (raw         80.264 )
~  mean/med:         117.3%      (raw        110.0%  )
~  min/med:          116.7%      (raw        109.0%  )
~  dev:        2.123e+06         (raw  2.123e+06     )
  test details: time: 500045957 ns, 30810000 cycles;  clocks: 471953434 (768933434 raw) sum, 9580000 cycles



 --------------------------------------- large %+d ----------------------------------------
    large %+d
---- testing function xsprintf
 cpu secs:
   avg call time:                 9.4798 ns
   avg calls/second:            105.5 m. calls
 cpu clocks:
-  min:               42         (raw         73     )
-  med50:             48         (raw         79     )
-  med90:             49         (raw         80     )
~  mean:              48.445     (raw         79.445 )
~  mean/med:         100.9%      (raw        100.6%  )
~  min/med:          114.3%      (raw        108.2%  )
~  dev:        1.166e+05         (raw  1.166e+05     )
  test details: time: 500058210 ns, 52750000 cycles;  clocks: 487837024 (800007024 raw) sum, 10070000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:                24.0836 ns
   avg calls/second:             41.5 m. calls
 cpu clocks:
-  min:               59         (raw         90     )
-  med50:             65         (raw         96     )
-  med90:             71         (raw        102     )
~  mean:              71.450     (raw        102.450 )
~  mean/med:         109.9%      (raw        106.7%  )
~  min/med:          110.2%      (raw        106.7%  )
~  dev:        9.300e+06         (raw  9.300e+06     )
  test details: time: 500215856 ns, 20770000 cycles;  clocks: 592322048 (849312048 raw) sum, 8290000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:                15.9204 ns
   avg calls/second:             62.8 m. calls
 cpu clocks:
-  min:               38         (raw         69     )
-  med50:             44         (raw         75     )
-  med90:             79         (raw        110     )
~  mean:              57.422     (raw         88.422 )
~  mean/med:         130.5%      (raw        117.9%  )
~  min/med:          115.8%      (raw        108.7%  )
~  dev:        1.614e+06         (raw  1.614e+06     )
  test details: time: 500059334 ns, 31410000 cycles;  clocks: 509330995 (784300995 raw) sum, 8870000 cycles



 --------------------------------------- large %5000d ----------------------------------------
    large %5000d
---- testing function xsprintf
 cpu secs:
   avg call time:                34.2407 ns
   avg calls/second:             29.2 m. calls
 cpu clocks:
-  min:               83         (raw        114     )
-  med50:             91         (raw        122     )
-  med90:            154         (raw        185     )
~  mean:             109.869     (raw        140.869 )
~  mean/med:         120.7%      (raw        115.5%  )
~  min/med:          109.6%      (raw        107.0%  )
~  dev:        1.858e+06         (raw  1.858e+06     )
  test details: time: 500257027 ns, 14610000 cycles;  clocks: 706458887 (905788887 raw) sum, 6430000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:                51.0604 ns
   avg calls/second:             19.6 m. calls
 cpu clocks:
-  min:              122         (raw        153     )
-  med50:            128         (raw        159     )
-  med90:            130         (raw        161     )
~  mean:             130.801     (raw        161.801 )
~  mean/med:         102.2%      (raw        101.8%  )
~  min/med:          104.9%      (raw        103.9%  )
~  dev:        8.802e+04         (raw  8.802e+04     )
  test details: time: 500391701 ns, 9800000 cycles;  clocks: 790040092 (977280092 raw) sum, 6040000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:                39.1727 ns
   avg calls/second:             25.5 m. calls
 cpu clocks:
-  min:              105         (raw        136     )
-  med50:            111         (raw        142     )
-  med90:            114         (raw        145     )
~  mean:             115.065     (raw        146.065 )
~  mean/med:         103.7%      (raw        102.9%  )
~  min/med:          105.7%      (raw        104.4%  )
~  dev:        1.602e+07         (raw  1.602e+07     )
  test details: time: 500234882 ns, 12770000 cycles;  clocks: 755980037 (959650037 raw) sum, 6570000 cycles



 --------------------------------------- large %+5000d ----------------------------------------
    large %+5000d
---- testing function xsprintf
 cpu secs:
   avg call time:                33.0525 ns
   avg calls/second:             30.3 m. calls
 cpu clocks:
-  min:               85         (raw        116     )
-  med50:             89         (raw        120     )
-  med90:             91         (raw        122     )
~  mean:              92.424     (raw        123.424 )
~  mean/med:         103.8%      (raw        102.9%  )
~  min/med:          104.7%      (raw        103.4%  )
~  dev:        5.687e+04         (raw  5.687e+04     )
  test details: time: 500084188 ns, 15130000 cycles;  clocks: 687634078 (918274078 raw) sum, 7440000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:                48.5886 ns
   avg calls/second:             20.6 m. calls
 cpu clocks:
-  min:              123         (raw        154     )
-  med50:            130         (raw        161     )
-  med90:            148         (raw        179     )
~  mean:             145.720     (raw        176.720 )
~  mean/med:         112.1%      (raw        109.8%  )
~  min/med:          105.7%      (raw        104.5%  )
~  dev:        2.561e+06         (raw  2.561e+06     )
  test details: time: 500462990 ns, 10300000 cycles;  clocks: 807287759 (979027759 raw) sum, 5540000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:                38.6839 ns
   avg calls/second:             25.9 m. calls
 cpu clocks:
-  min:              105         (raw        136     )
-  med50:            111         (raw        142     )
-  med90:            113         (raw        144     )
~  mean:             112.590     (raw        143.590 )
~  mean/med:         101.4%      (raw        101.1%  )
~  min/med:          105.7%      (raw        104.4%  )
~  dev:        3.609e+04         (raw  3.609e+04     )
  test details: time: 500182523 ns, 12930000 cycles;  clocks: 747599085 (953439085 raw) sum, 6640000 cycles



 --------------------------------------- large %+05000d ----------------------------------------
    large %+05000d
---- testing function xsprintf
 cpu secs:
   avg call time:                33.3343 ns
   avg calls/second:             30.0 m. calls
 cpu clocks:
-  min:               87         (raw        118     )
-  med50:             93         (raw        124     )
-  med90:             97         (raw        128     )
~  mean:              96.250     (raw        127.250 )
~  mean/med:         103.5%      (raw        102.6%  )
~  min/med:          106.9%      (raw        105.1%  )
~  dev:        1.403e+05         (raw  1.403e+05     )
  test details: time: 500015131 ns, 15000000 cycles;  clocks: 693962224 (917472224 raw) sum, 7210000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:                49.1546 ns
   avg calls/second:             20.3 m. calls
 cpu clocks:
-  min:              127         (raw        158     )
-  med50:            133         (raw        164     )
-  med90:            136         (raw        167     )
~  mean:             136.201     (raw        167.201 )
~  mean/med:         102.4%      (raw        102.0%  )
~  min/med:          104.7%      (raw        103.8%  )
~  dev:        1.469e+05         (raw  1.469e+05     )
  test details: time: 500394163 ns, 10180000 cycles;  clocks: 803587487 (986487487 raw) sum, 5900000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:                38.1793 ns
   avg calls/second:             26.2 m. calls
 cpu clocks:
-  min:              107         (raw        138     )
-  med50:            113         (raw        144     )
-  med90:            128         (raw        159     )
~  mean:             121.228     (raw        152.228 )
~  mean/med:         107.3%      (raw        105.7%  )
~  min/med:          105.6%      (raw        104.3%  )
~  dev:        5.669e+05         (raw  5.669e+05     )
  test details: time: 500148834 ns, 13100000 cycles;  clocks: 757673112 (951423112 raw) sum, 6250000 cycles



 --------------------------------------- large %+020d ----------------------------------------
    large %+020d
---- testing function xsprintf
 cpu secs:
   avg call time:                13.4272 ns
   avg calls/second:             74.5 m. calls
 cpu clocks:
-  min:               47         (raw         78     )
-  med50:             53         (raw         84     )
-  med90:             55         (raw         86     )
~  mean:              61.491     (raw         92.491 )
~  mean/med:         116.0%      (raw        110.1%  )
~  min/med:          112.8%      (raw        107.7%  )
~  dev:        2.636e+06         (raw  2.636e+06     )
  test details: time: 500027795 ns, 37240000 cycles;  clocks: 538658771 (810218771 raw) sum, 8760000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:                29.2502 ns
   avg calls/second:             34.2 m. calls
 cpu clocks:
-  min:               69         (raw        100     )
-  med50:             77         (raw        108     )
-  med90:             91         (raw        122     )
~  mean:              86.689     (raw        117.689 )
~  mean/med:         112.6%      (raw        109.0%  )
~  min/med:          111.6%      (raw        108.0%  )
~  dev:        2.565e+06         (raw  2.565e+06     )
  test details: time: 500178400 ns, 17100000 cycles;  clocks: 650164846 (882664846 raw) sum, 7500000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:                21.5668 ns
   avg calls/second:             46.4 m. calls
 cpu clocks:
-  min:               47         (raw         78     )
-  med50:             52         (raw         83     )
-  med90:             54         (raw         85     )
~  mean:              53.966     (raw         84.966 )
~  mean/med:         103.8%      (raw        102.4%  )
~  min/med:          110.6%      (raw        106.4%  )
~  dev:        1.784e+04         (raw  1.784e+04     )
  test details: time: 500134694 ns, 23190000 cycles;  clocks: 520773205 (819923205 raw) sum, 9650000 cycles



 --------------------------------------- zero %x ----------------------------------------
    zero %x
---- testing function xsprintf
 cpu secs:
   avg call time:                 6.1019 ns
   avg calls/second:            163.9 m. calls
 cpu clocks:
-  min:               28         (raw         59     )
-  med50:             34         (raw         65     )
-  med90:             38         (raw         69     )
~  mean:              35.833     (raw         66.833 )
~  mean/med:         105.4%      (raw        102.8%  )
~  min/med:          121.4%      (raw        110.2%  )
~  dev:        1.613e+05         (raw  1.613e+05     )
  test details: time: 500051275 ns, 81950000 cycles;  clocks: 392373416 (731823416 raw) sum, 10950000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:                21.2345 ns
   avg calls/second:             47.1 m. calls
 cpu clocks:
-  min:               52         (raw         83     )
-  med50:             57         (raw         88     )
-  med90:             60         (raw         91     )
~  mean:              61.961     (raw         92.961 )
~  mean/med:         108.7%      (raw        105.6%  )
~  min/med:          109.6%      (raw        106.0%  )
~  dev:        1.217e+06         (raw  1.217e+06     )
  test details: time: 500284150 ns, 23560000 cycles;  clocks: 555789252 (833859252 raw) sum, 8970000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:                12.3830 ns
   avg calls/second:             80.8 m. calls
 cpu clocks:
-  min:               26         (raw         57     )
-  med50:             34         (raw         65     )
-  med90:             44         (raw         75     )
~  mean:              37.806     (raw         68.806 )
~  mean/med:         111.2%      (raw        105.9%  )
~  min/med:          130.8%      (raw        114.0%  )
~  dev:        2.365e+06         (raw  2.365e+06     )
  test details: time: 500025310 ns, 40380000 cycles;  clocks: 403393972 (734163972 raw) sum, 10670000 cycles



 --------------------------------------- little %x ----------------------------------------
    little %x
---- testing function xsprintf
 cpu secs:
   avg call time:                 6.1270 ns
   avg calls/second:            163.2 m. calls
 cpu clocks:
-  min:               28         (raw         59     )
-  med50:             34         (raw         65     )
-  med90:             38         (raw         69     )
~  mean:              35.804     (raw         66.804 )
~  mean/med:         105.3%      (raw        102.8%  )
~  min/med:          121.4%      (raw        110.2%  )
~  dev:        3.232e+05         (raw  3.232e+05     )
  test details: time: 500027409 ns, 81610000 cycles;  clocks: 401359565 (748869565 raw) sum, 11210000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:                22.3027 ns
   avg calls/second:             44.8 m. calls
 cpu clocks:
-  min:               55         (raw         86     )
-  med50:             60         (raw         91     )
-  med90:             62         (raw         93     )
~  mean:              61.934     (raw         92.934 )
~  mean/med:         103.2%      (raw        102.1%  )
~  min/med:          109.1%      (raw        105.8%  )
~  dev:        4.048e+04         (raw  4.048e+04     )
  test details: time: 500026930 ns, 22420000 cycles;  clocks: 553074987 (829904987 raw) sum, 8930000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:                12.7897 ns
   avg calls/second:             78.2 m. calls
 cpu clocks:
-  min:               28         (raw         59     )
-  med50:             34         (raw         65     )
-  med90:             36         (raw         67     )
~  mean:              35.077     (raw         66.077 )
~  mean/med:         103.2%      (raw        101.7%  )
~  min/med:          121.4%      (raw        110.2%  )
~  dev:        1.072e+05         (raw  1.072e+05     )
  test details: time: 500076340 ns, 39100000 cycles;  clocks: 396726229 (747336229 raw) sum, 11310000 cycles



 --------------------------------------- medium %x ----------------------------------------
    medium %x
---- testing function xsprintf
 cpu secs:
   avg call time:                 6.5706 ns
   avg calls/second:            152.2 m. calls
 cpu clocks:
-  min:               28         (raw         59     )
-  med50:             36         (raw         67     )
-  med90:             58         (raw         89     )
~  mean:              42.818     (raw         73.818 )
~  mean/med:         118.9%      (raw        110.2%  )
~  min/med:          128.6%      (raw        113.6%  )
~  dev:        8.275e+04         (raw  8.275e+04     )
  test details: time: 500023920 ns, 76100000 cycles;  clocks: 426466059 (735226059 raw) sum, 9960000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:                23.6239 ns
   avg calls/second:             42.3 m. calls
 cpu clocks:
-  min:               58         (raw         89     )
-  med50:             62         (raw         93     )
-  med90:             64         (raw         95     )
~  mean:              64.268     (raw         95.268 )
~  mean/med:         103.7%      (raw        102.4%  )
~  min/med:          106.9%      (raw        104.5%  )
~  dev:        4.102e+04         (raw  4.102e+04     )
  test details: time: 500118737 ns, 21170000 cycles;  clocks: 573913220 (850743220 raw) sum, 8930000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:                17.0490 ns
   avg calls/second:             58.7 m. calls
 cpu clocks:
-  min:               40         (raw         71     )
-  med50:             46         (raw         77     )
-  med90:             54         (raw         85     )
~  mean:              53.905     (raw         84.905 )
~  mean/med:         117.2%      (raw        110.3%  )
~  min/med:          115.0%      (raw        108.5%  )
~  dev:        6.518e+06         (raw  6.518e+06     )
  test details: time: 500047824 ns, 29330000 cycles;  clocks: 493226412 (776876412 raw) sum, 9150000 cycles



 --------------------------------------- large %x ----------------------------------------
    large %x
---- testing function xsprintf
 cpu secs:
   avg call time:                 7.0024 ns
   avg calls/second:            142.8 m. calls
 cpu clocks:
-  min:               29         (raw         60     )
-  med50:             36         (raw         67     )
-  med90:             38         (raw         69     )
~  mean:              36.894     (raw         67.894 )
~  mean/med:         102.5%      (raw        101.3%  )
~  min/med:          124.1%      (raw        111.7%  )
~  dev:        1.498e+05         (raw  1.498e+05     )
  test details: time: 500040792 ns, 71410000 cycles;  clocks: 408417761 (751587761 raw) sum, 11070000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:                32.9447 ns
   avg calls/second:             30.4 m. calls
 cpu clocks:
-  min:               63         (raw         94     )
-  med50:             71         (raw        102     )
-  med90:             89         (raw        120     )
~  mean:              79.086     (raw        110.086 )
~  mean/med:         111.4%      (raw        107.9%  )
~  min/med:          112.7%      (raw        108.5%  )
~  dev:        7.603e+04         (raw  7.603e+04     )
  test details: time: 500100852 ns, 15180000 cycles;  clocks: 616080321 (857570321 raw) sum, 7790000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:                22.2391 ns
   avg calls/second:             45.0 m. calls
 cpu clocks:
-  min:               50         (raw         81     )
-  med50:             57         (raw         88     )
-  med90:             68         (raw         99     )
~  mean:              63.566     (raw         94.566 )
~  mean/med:         111.5%      (raw        107.5%  )
~  min/med:          114.0%      (raw        108.6%  )
~  dev:        8.747e+04         (raw  8.747e+04     )
  test details: time: 500158198 ns, 22490000 cycles;  clocks: 559377590 (832177590 raw) sum, 8800000 cycles



 --------------------------------------- large %#x ----------------------------------------
    large %#x
---- testing function xsprintf
 cpu secs:
   avg call time:                 7.5599 ns
   avg calls/second:            132.3 m. calls
 cpu clocks:
-  min:               30         (raw         61     )
-  med50:             36         (raw         67     )
-  med90:             38         (raw         69     )
~  mean:              36.574     (raw         67.574 )
~  mean/med:         101.6%      (raw        100.9%  )
~  min/med:          120.0%      (raw        109.8%  )
~  dev:        1.262e+05         (raw  1.262e+05     )
  test details: time: 500012273 ns, 66140000 cycles;  clocks: 398289515 (735879515 raw) sum, 10890000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:                31.4447 ns
   avg calls/second:             31.8 m. calls
 cpu clocks:
-  min:               68         (raw         99     )
-  med50:             75         (raw        106     )
-  med90:             97         (raw        128     )
~  mean:              84.480     (raw        115.480 )
~  mean/med:         112.6%      (raw        108.9%  )
~  min/med:          110.3%      (raw        107.1%  )
~  dev:        5.233e+04         (raw  5.233e+04     )
  test details: time: 500285061 ns, 15910000 cycles;  clocks: 646273891 (883423891 raw) sum, 7650000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:                27.3714 ns
   avg calls/second:             36.5 m. calls
 cpu clocks:
-  min:               52         (raw         83     )
-  med50:             67         (raw         98     )
-  med90:            115         (raw        146     )
~  mean:              79.816     (raw        110.816 )
~  mean/med:         119.1%      (raw        113.1%  )
~  min/med:          128.8%      (raw        118.1%  )
~  dev:        3.295e+06         (raw  3.295e+06     )
  test details: time: 500075980 ns, 18270000 cycles;  clocks: 600216395 (833336395 raw) sum, 7520000 cycles



 --------------------------------------- padded %x ----------------------------------------
    padded %x
---- testing function xsprintf
 cpu secs:
   avg call time:                 7.4132 ns
   avg calls/second:            134.9 m. calls
 cpu clocks:
-  min:               30         (raw         61     )
-  med50:             38         (raw         69     )
-  med90:             40         (raw         71     )
~  mean:              40.572     (raw         71.572 )
~  mean/med:         106.8%      (raw        103.7%  )
~  min/med:          126.7%      (raw        113.1%  )
~  dev:        2.815e+04         (raw  2.815e+04     )
  test details: time: 500019059 ns, 67450000 cycles;  clocks: 429253609 (757233609 raw) sum, 10580000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:                32.1012 ns
   avg calls/second:             31.2 m. calls
 cpu clocks:
-  min:               62         (raw         93     )
-  med50:             69         (raw        100     )
-  med90:             80         (raw        111     )
~  mean:              75.346     (raw        106.346 )
~  mean/med:         109.2%      (raw        106.3%  )
~  min/med:          111.3%      (raw        107.5%  )
~  dev:        6.216e+04         (raw  6.216e+04     )
  test details: time: 500137058 ns, 15580000 cycles;  clocks: 607292195 (857152195 raw) sum, 8060000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:                17.6705 ns
   avg calls/second:             56.6 m. calls
 cpu clocks:
-  min:               40         (raw         71     )
-  med50:             46         (raw         77     )
-  med90:             49         (raw         80     )
~  mean:              48.748     (raw         79.748 )
~  mean/med:         106.0%      (raw        103.6%  )
~  min/med:          115.0%      (raw        108.5%  )
~  dev:        2.825e+05         (raw  2.825e+05     )
  test details: time: 500075135 ns, 28300000 cycles;  clocks: 487969636 (798279636 raw) sum, 10010000 cycles



 --------------------------------------- padded %llx ----------------------------------------
    padded %llx
---- testing function xsprintf
 cpu secs:
   avg call time:                10.9776 ns
   avg calls/second:             91.1 m. calls
 cpu clocks:
-  min:               32         (raw         63     )
-  med50:             40         (raw         71     )
-  med90:             48         (raw         79     )
~  mean:              45.861     (raw         76.861 )
~  mean/med:         114.7%      (raw        108.3%  )
~  min/med:          125.0%      (raw        112.7%  )
~  dev:        7.124e+05         (raw  7.124e+05     )
  test details: time: 500029277 ns, 45550000 cycles;  clocks: 448522926 (751702926 raw) sum, 9780000 cycles
---- testing function sprintf
 cpu secs:
   avg call time:                30.0012 ns
   avg calls/second:             33.3 m. calls
 cpu clocks:
-  min:               70         (raw        101     )
-  med50:             77         (raw        108     )
-  med90:            101         (raw        132     )
~  mean:              87.716     (raw        118.716 )
~  mean/med:         113.9%      (raw        109.9%  )
~  min/med:          110.0%      (raw        106.9%  )
~  dev:        1.673e+05         (raw  1.673e+05     )
  test details: time: 500119759 ns, 16670000 cycles;  clocks: 656989731 (889179731 raw) sum, 7490000 cycles
---- testing function stbsp_sprintf
 cpu secs:
   avg call time:                22.2853 ns
   avg calls/second:             44.9 m. calls
 cpu clocks:
-  min:               54         (raw         85     )
-  med50:             68         (raw         99     )
-  med90:            105         (raw        136     )
~  mean:              82.595     (raw        113.595 )
~  mean/med:         121.5%      (raw        114.7%  )
~  min/med:          125.9%      (raw        116.5%  )
~  dev:        1.230e+06         (raw  1.230e+06     )
  test details: time: 500083182 ns, 22440000 cycles;  clocks: 605417792 (832647792 raw) sum, 7330000 cycles


| Realization \ Test         | general         | empty call      | medium parts    | long parts      |

|----------------------------|-----------------|-----------------|-----------------|-----------------|| xsprintf        min cycles |         135     |           4     |          63     |         572     |
|                 m50 cycles |         146     |          10     |          75     |         592     |
|                 avg time   |       45.637 ns |        1.447 ns |       23.373 ns |      248.552 ns |
|----------------------------|-----------------|-----------------|-----------------|-----------------|
|----------------------------|-----------------|-----------------|-----------------|-----------------|| sprintf         min cycles |         298     |          26     |         101     |         617     |
|                 m50 cycles |         337     |          34     |         111     |         654     |
|                 avg time   |      135.450 ns |        9.083 ns |       44.086 ns |      275.383 ns |
|----------------------------|-----------------|-----------------|-----------------|-----------------|
|----------------------------|-----------------|-----------------|-----------------|-----------------|| stbsp_sprintf   min cycles |         229     |          14     |         117     |        3985     |
|                 m50 cycles |         257     |          18     |         131     |        4057     |
|                 avg time   |      109.693 ns |        3.981 ns |       58.529 ns |     1806.055 ns |
|----------------------------|-----------------|-----------------|-----------------|-----------------|


| Realization \ Test         | group parsing   | bad groups      | variable width  | little space    |

| xsprintf        min cycles |         259     |         652     |         239     |         267     |
|                 m50 cycles |         269     |         674     |         290     |         280     |
|                 avg time   |      113.607 ns |      287.583 ns |      112.286 ns |      117.319 ns |
|----------------------------|-----------------|-----------------|-----------------|-----------------|
| sprintf         min cycles |         623     |         759     |         672     |         714     |
|                 m50 cycles |         643     |         867     |         849     |         870     |
|                 avg time   |      276.801 ns |      376.516 ns |      409.696 ns |      351.041 ns |
|----------------------------|-----------------|-----------------|-----------------|-----------------|
| stbsp_sprintf   min cycles |         661     |         824     |         904     |         946     |
|                 m50 cycles |         798     |        1003     |        1025     |        1057     |
|                 avg time   |      334.894 ns |      423.376 ns |      428.044 ns |      470.322 ns |
|----------------------------|-----------------|-----------------|-----------------|-----------------|


| Realization \ Test         | large space     | large zero      | little -padd    | large -padd     |

| xsprintf        min cycles |         200     |         200     |         310     |         201     |
|                 m50 cycles |         221     |         222     |         337     |         221     |
|                 avg time   |       93.404 ns |       92.932 ns |      137.956 ns |       96.229 ns |
|----------------------------|-----------------|-----------------|-----------------|-----------------|
| sprintf         min cycles |         245     |         245     |         761     |         242     |
|                 m50 cycles |         251     |         251     |         822     |         249     |
|                 avg time   |       99.348 ns |       95.632 ns |      363.146 ns |      105.767 ns |
|----------------------------|-----------------|-----------------|-----------------|-----------------|
| stbsp_sprintf   min cycles |         227     |         227     |        1009     |         231     |
|                 m50 cycles |         233     |         233     |        1159     |         239     |
|                 avg time   |       87.798 ns |       88.867 ns |      500.983 ns |       90.271 ns |
|----------------------------|-----------------|-----------------|-----------------|-----------------|


| Realization \ Test         | empty string-1  | empty string-2  | empty string-3  | medium string   |

| xsprintf        min cycles |          26     |          28     |          28     |          51     |
|                 m50 cycles |          32     |          38     |          36     |          59     |
|                 avg time   |        6.411 ns |        8.396 ns |        6.868 ns |       15.306 ns |
|----------------------------|-----------------|-----------------|-----------------|-----------------|
| sprintf         min cycles |          42     |          42     |          45     |          91     |
|                 m50 cycles |          46     |          48     |          51     |          99     |
|                 avg time   |       16.844 ns |       15.759 ns |       16.435 ns |       38.253 ns |
|----------------------------|-----------------|-----------------|-----------------|-----------------|
| stbsp_sprintf   min cycles |          24     |          24     |          24     |         138     |
|                 m50 cycles |          30     |          30     |          30     |         146     |
|                 avg time   |       11.581 ns |       12.019 ns |       12.216 ns |       63.890 ns |
|----------------------------|-----------------|-----------------|-----------------|-----------------|


| Realization \ Test         | large string    | small %float    | precise %float  | very %float     |

| xsprintf        min cycles |         824     |         180     |         180     |         182     |
|                 m50 cycles |         906     |         186     |         188     |         189     |
|                 avg time   |      418.506 ns |       47.595 ns |       48.906 ns |       50.991 ns |
|----------------------------|-----------------|-----------------|-----------------|-----------------|
| sprintf         min cycles |         641     |         134     |         776     |       28785     |
|                 m50 cycles |         682     |         151     |         861     |       31624     |
|                 avg time   |      284.267 ns |       60.415 ns |      355.500 ns |    12870.963 ns |
|----------------------------|-----------------|-----------------|-----------------|-----------------|
| stbsp_sprintf   min cycles |        7133     |          99     |         105     |         149     |
|                 m50 cycles |        7423     |         107     |         111     |         158     |
|                 avg time   |     3246.073 ns |       32.154 ns |       43.759 ns |       62.185 ns |
|----------------------------|-----------------|-----------------|-----------------|-----------------|


| Realization \ Test         | small %e float  | one digit %e    | normal %e float | large %e float  |

| xsprintf        min cycles |          68     |          58     |          73     |         115     |
|                 m50 cycles |          73     |          63     |          79     |         137     |
|                 avg time   |       14.564 ns |       12.046 ns |       19.033 ns |       43.712 ns |
|----------------------------|-----------------|-----------------|-----------------|-----------------|
| sprintf         min cycles |         135     |         101     |         204     |       28729     |
|                 m50 cycles |         150     |         111     |         237     |       31616     |
|                 avg time   |       58.395 ns |       45.416 ns |      102.460 ns |    12896.735 ns |
|----------------------------|-----------------|-----------------|-----------------|-----------------|
| stbsp_sprintf   min cycles |         101     |          86     |         119     |         152     |
|                 m50 cycles |         107     |          93     |         127     |         160     |
|                 avg time   |       33.270 ns |       27.451 ns |       41.534 ns |       59.704 ns |
|----------------------------|-----------------|-----------------|-----------------|-----------------|


| Realization \ Test         | zero %u         | little %u       | medium %u       | large %u        |

| xsprintf        min cycles |          34     |          38     |          47     |          65     |
|                 m50 cycles |          40     |          44     |          54     |          71     |
|                 avg time   |        8.345 ns |        9.573 ns |       10.160 ns |       14.293 ns |
|----------------------------|-----------------|-----------------|-----------------|-----------------|
| sprintf         min cycles |          50     |          54     |          72     |         109     |
|                 m50 cycles |          56     |          61     |          79     |         117     |
|                 avg time   |       20.068 ns |       23.341 ns |       25.531 ns |       36.632 ns |
|----------------------------|-----------------|-----------------|-----------------|-----------------|
| stbsp_sprintf   min cycles |          34     |          36     |          52     |          62     |
|                 m50 cycles |          38     |          42     |          58     |          68     |
|                 avg time   |       15.704 ns |       14.106 ns |       20.079 ns |       25.304 ns |
|----------------------------|-----------------|-----------------|-----------------|-----------------|


| Realization \ Test         | zero %d         | little %d       | medium %d       | large %d        |

| xsprintf        min cycles |          36     |          40     |          50     |          40     |
|                 m50 cycles |          41     |          44     |          54     |          46     |
|                 avg time   |        9.243 ns |        9.108 ns |       10.419 ns |       10.071 ns |
|----------------------------|-----------------|-----------------|-----------------|-----------------|
| sprintf         min cycles |          50     |          55     |          75     |          58     |
|                 m50 cycles |          56     |          61     |          83     |          63     |
|                 avg time   |       21.766 ns |       26.739 ns |       24.517 ns |       22.556 ns |
|----------------------------|-----------------|-----------------|-----------------|-----------------|
| stbsp_sprintf   min cycles |          32     |          34     |          52     |          36     |
|                 m50 cycles |          38     |          40     |          57     |          42     |
|                 avg time   |       13.291 ns |       13.181 ns |       18.698 ns |       16.230 ns |
|----------------------------|-----------------|-----------------|-----------------|-----------------|


| Realization \ Test         | large %+d       | large %5000d    | large %+5000d   | large %+05000d  |

| xsprintf        min cycles |          42     |          83     |          85     |          87     |
|                 m50 cycles |          48     |          91     |          89     |          93     |
|                 avg time   |        9.480 ns |       34.241 ns |       33.052 ns |       33.334 ns |
|----------------------------|-----------------|-----------------|-----------------|-----------------|
| sprintf         min cycles |          59     |         122     |         123     |         127     |
|                 m50 cycles |          65     |         128     |         130     |         133     |
|                 avg time   |       24.084 ns |       51.060 ns |       48.589 ns |       49.155 ns |
|----------------------------|-----------------|-----------------|-----------------|-----------------|
| stbsp_sprintf   min cycles |          38     |         105     |         105     |         107     |
|                 m50 cycles |          44     |         111     |         111     |         113     |
|                 avg time   |       15.920 ns |       39.173 ns |       38.684 ns |       38.179 ns |
|----------------------------|-----------------|-----------------|-----------------|-----------------|


| Realization \ Test         | large %+020d    | zero %x         | little %x       | medium %x       |

| xsprintf        min cycles |          47     |          28     |          28     |          28     |
|                 m50 cycles |          53     |          34     |          34     |          36     |
|                 avg time   |       13.427 ns |        6.102 ns |        6.127 ns |        6.571 ns |
|----------------------------|-----------------|-----------------|-----------------|-----------------|
| sprintf         min cycles |          69     |          52     |          55     |          58     |
|                 m50 cycles |          77     |          57     |          60     |          62     |
|                 avg time   |       29.250 ns |       21.234 ns |       22.303 ns |       23.624 ns |
|----------------------------|-----------------|-----------------|-----------------|-----------------|
| stbsp_sprintf   min cycles |          47     |          26     |          28     |          40     |
|                 m50 cycles |          52     |          34     |          34     |          46     |
|                 avg time   |       21.567 ns |       12.383 ns |       12.790 ns |       17.049 ns |
|----------------------------|-----------------|-----------------|-----------------|-----------------|


| Realization \ Test         | large %x        | large %#x       | padded %x       | padded %llx     |

| xsprintf        min cycles |          29     |          30     |          30     |          32     |
|                 m50 cycles |          36     |          36     |          38     |          40     |
|                 avg time   |        7.002 ns |        7.560 ns |        7.413 ns |       10.978 ns |
|----------------------------|-----------------|-----------------|-----------------|-----------------|
| sprintf         min cycles |          63     |          68     |          62     |          70     |
|                 m50 cycles |          71     |          75     |          69     |          77     |
|                 avg time   |       32.945 ns |       31.445 ns |       32.101 ns |       30.001 ns |
|----------------------------|-----------------|-----------------|-----------------|-----------------|
| stbsp_sprintf   min cycles |          50     |          52     |          40     |          54     |
|                 m50 cycles |          57     |          67     |          46     |          68     |
|                 avg time   |       22.239 ns |       27.371 ns |       17.670 ns |       22.285 ns |
|----------------------------|-----------------|-----------------|-----------------|-----------------|
function xsprintf             scored:
         30 medals in category min_cycles
         29 medals in category m50_cycles
         38 medals in category avg_time
function sprintf              scored:
          1 medals in category min_cycles
          1 medals in category m50_cycles
          1 medals in category avg_time
function stbsp_sprintf        scored:
         16 medals in category min_cycles
         16 medals in category m50_cycles
          5 medals in category avg_time

Function scores: [min]
  xsprintf            :       5814 [     +5012]
  sprintf             :      66479 [    +65677]
  stbsp_sprintf       :      18558 [    +17756]
Function scores: [m50]
  xsprintf            :       6345 [     +5461]
  sprintf             :      73194 [    +72310]
  stbsp_sprintf       :      19898 [    +19014]
Function scores: [avg]
  xsprintf            :      2319.16 ns
  sprintf             :     29900.33 ns
  stbsp_sprintf       :      8470.55 ns
