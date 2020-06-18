import matplotlib.pyplot as plt
import numpy as np
from math import log10
# str_vals = "2102151,1372201,766670,763063,667467,488619,476650,461616,425566,375441,342712,297091,292447,257802,237667,232213,225603,221880,220269,217410,204560,185098,184045,180987,174184,172712,168577,167752,166842,162443,158945,152002,151212,150470,146837,146250,141000,138581,138396,137765,137482,133762,131451,131263,129353,128340,126571,126474,125010,122353,120801,119025,118936,117847,117268,116439,114450,111549,110528,110112,105487,104723,103010,101697,99394,98045,96649,96098,94002,93724,93235,92396,92243,92225,92086,90607,89813,89654,89050,88982,88901,88866,88569,87476,87442,87167,87111,86722,86715,86546,85869,85472,85283,85075,84899,83395,83349,83053,81926,81919,81265,81203,78702,77140,77079,76874,76493,76446,76256,75227,74651,73837,73375,73291,72857,72657,72534,72495,71059,70358,70122,69595,68998,68610,67579,67495,66798,66517,65869,65333,65139,64768,64728,64433,62803,62593,62426,62064,62058,61970,61675,61581,61084,61013,60063,59632,59514,59419,59168,58730,57293,56328,56320,56090,55602,55589,55469,55446,55131,55122,54694,54668,54594,54019,53619,53578,53332,53036,52871,51941,51795,51524,51276,51051,49841,49785,49769,49445,49380,48942,48618,48408,48314,48248,48186,47960,46927,46555,46110,45849,45683,45217,45101,44991,44809,44636,44603,44564,44264,43733,43674,43523,43366,43331,42716,42262,42139,41843,41554,41337,41112,41102,41082,40910,40492,40156,40051,39934,39714,39498,39468,39303,39291,39210,39149,38930,38926,38886,38883,38869,38553,38439,37914,37806,37775,37662,37608,37549,37496,37454,37314,36972,36823,36814,36552,36240,36237,36126,35913,35800,35727,35707,35677,35603,35400,34870,34667,34626,34551,34412,34201,34111,34087,34002,33906,33889,33724,33545,33441,33191,32878,32791,32732,32579,32344,32143,32086,32056,31820,31466,31373,31344,31263,31249,31048,30856,30704,30565,30547,30508,30338,30205,30000,29972,29956,29764,29566,29327,29263,29256,29181,29129,29003,28926,28845,28742,28629,28601,28385,28076,28051,28042,28030,28004,27931,27907,27851,27694,27688,27592,27591,27498,27345,27330,27272,27202,27162,26956,26888,26841,26785,26629,26603,26529,26491,26454,26302,26166,26004,25939,25897,25827,25818,25693,25654,25557,25554,25533,25507,25368,25279,25136,25113,25055,25011,24927,24855,24852,24789,24638,24596,24533,24493,24341,24339,24275,24127,24120,24086,23885,23834,23720,23682,23680,23658,23647,23642,23607,23504,23500,23469,23422,23287,23216,23209,23182,23175,23108,23055,23027,23023,22886,22797,22775,22730,22724,22707,22669,22665,22648,22618,22609,22525,22500,22416,22363,22250,22246,22245,22241,22166,21884,21829,21810,21753,21725,21664,21523,21453,21447,21425,21414,21392,21377,21375,21338,21323,21227,21186,21137,21085,21082,21074,20985,20857,20854,20764,20678,20628,20619,20615,20535,20520,20509,20458,20444,20373,20372,20251,20164,20120,20113,20080,19994,19982,19964,19962,19954,19954,19939,19918,19893,19837,19783,19766,19735,19704,19687,19611,19599,19446,19441,19427,19346,19327,19235,19216,19211,19202,19146,19136,19085,19026,19014,18984,18927,18814,18706,18561,18507,18400,18369,18340,18271,18257,18246,18213,18205,18192,18185,18149,18147,18130,18030,17901,17856,17849,17831,17799,17778,17757,17739,17727,17615,17605,17595,17560,17535,17479,17470,17447,17388,17384,17382,17374,17242,17212,17156,17153,17123,17088,17052,17049,17047,17008,16996,16940,16910,16847,16763,16715,16699,16680,16655,16626,16566,16553,16547,16543,16540,16539,16510,16489,16476,16426,16401,16348,16348,16342,16315,16269,16268,16267,16214,16158,16128,16075,16055,16040,16028,16024,16007,15924,15883,15835,15819,15786,15681,15679,15595,15589,15580,15561,15545,15531,15514,15430,15426,15418,15414,15364,15364,15322,15287,15277,15262,15257,15235,15123,15105,15060,15034,15020,14965,14920,14901,14896,14893,14872,14853,14852,14847,14812,14809,14757,14741,14736,14668,14662,14657,14633,14609,14587,14587,14571,14564,14561,14536,14535,14520,14451,14433,14380,14341,14334,14319,14319,14286,14281,14276,14237,14199,14164,14155,14142,14130,14108,14078,14040,14017,13995,13924,13917,13899,13872,13854,13847,13845,13832,13797,13780,13754,13738,13732,13684,13662,13659,13580,13576,13508,13487,13477,13476,13443,13438,13433,13403,13386,13374,13366,13331,13325,13314,13302,13300,13298,13279,13257,13248,13228,13215,13215,13184,13179,13166,13157,13144,13131,13125,13116,13071,13068,13063,13063,13060,13015,12979,12964,12948,12920,12903,12894,12891,12874,12831,12811,12801,12793,12761,12758,12733,12727,12712,12710,12692,12674,12670,12604,12599,12575,12557,12551,12544,12481,12459,12442,12435,12424,12375,12361,12329,12321,12314,12299,12292,12281,12278,12272,12237,12199,12165,12157,12150,12144,12142,12119,12110,12105,12090,12086,12084,12082,12076,12054,12052,12050,12003,11994,11991,11976,11961,11949,11948,11901,11895,11892,11882,11881,11879,11878,11862,11847,11835,11832,11825,11813,11800,11749,11738,11733,11711,11696,11675,11674,11627,11625,11591,11586,11573,11565,11563,11518,11504,11499,11498,11464,11462,11433,11428,11396,11378,11372,11339,11324,11323,11306,11293,11258,11250,11244,11213,11213,11203,11202,11197,11193,11191,11170,11162,11153,11146,11140,11103,11097,11091,11090,11077,11076,11070,11063,11048,11012,10992,10982,10969,10963,10960,10948,10941,10939,10931,10900,10877,10876,10856,10854,10853,10846,10837,10824,10817,10815,10807,10796,10794,10793,10789,10789,10729,10716,10712,10705,10678,10665,10652,10650,10638,10633,10633,10632,10621,10599,10598,10588,10551,10544,10543,10504,10502,10481,10459,10459,10445,10442,10441,10437,10420,10398,10394,10387,10386,10384,10375,10370,10354,10327,10319,10316,10305,10305,10301,10295,10289,10270,10269,10246,10229,10225,10224,10210,10208,10160,10134,10134,10132,10129,10126,10123,10101,10074,10051,10051,10030,10023,10008,9998,9985,9982,9981,9976,9972,9953,9945,9938,9928,9927,9926,9921,9904,9881,9880,9879,9857,9844,9836,9795,9792,9771,9769,9757,9755,9743,9732,9723,9719,9719,9715,9713,9708,9703,9672,9669,9662,9655,9638,9624,9622,9616,9601,9598,9582,9557,9555,9537,9535,9529,9520,9517,9512,9510,9509,9504,9503,9452,9436,9433,9429,9422,9414,9411,9403,4585,2990,2184,1687,1372,1164,1000,871,770,685,619,562,517,475,439,406,378,354,332,312,295,280,265,252,240,229,218,209,200,192,185,177,170,164,158,152,147,143,138,133,129,125,122,118,115,112,108,106,103,100,98,95,93,90,88,86,84,82,80,78,76,75,73,72,70,69,67,66,64,63,62,61,59,58,57,56,55,54,53,52,51,50,49,49,48,47,46,45,45,44,43,42,42,41,40,40,39,39,38,38,37,36,36,35,35,34,34,33,33,32,32,32,31,31,30,30,29,29,29,28,28,28,27,27,27,26,26,26,25,25,25,24,24,24,24,23,23,23,22,22,22,22,21,21,21,21,21,20,20,20,20,20,19,19,19,19,19,18,18,18,18,18,17,17,17,17,17,17,17,16,16,16,16,16,16,15,15,15,15,15,15,15,15,14,14,14,14,14,14,14,14,14,13,13,13,13,13,13,13,13,13,12,12,12,12,12,12,12,12,12,12,12,11,11,11,11,11,11,11,11,11,11,11,11,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1"
file = open('/home/kprlns/Desktop/Mag1Cource/2sem/NLP/MetricsEvaluator/tmp.txt', 'r')

str_vals = file.readline()[:-2]
file.close()

print(len(str_vals.split(',')))

tmp_vals = str_vals.split(',')
vals = []
for i in range(len(tmp_vals)):
    vals.append(int(tmp_vals[i]))


ticksx = []
val_filtered = [] #vals[1:500]
cnt = 1
while cnt < len(vals) and cnt < 10001:
    val_filtered.append(log10(vals[cnt]))
    cnt *= 10

#for i in range(100, len(vals), 10000):
#    val_filtered.append(vals[i])

print(len(val_filtered))
print(val_filtered)
deltas = []
for i in range(1, len(val_filtered)):
    deltas.append(val_filtered[i] / val_filtered[i - 1])

#print(deltas)
print('------')
ticksx = []
for i in range(len(val_filtered)):
    #ticksx.append(i)
    ticksx.append(10**i)


#for i in range(len(vals)):
#    vals[i] = vals[i] * i

plt.plot(val_filtered)
plt.xticks(np.arange(len(val_filtered)), ticksx)
plt.xlabel('Номер терма')
plt.ylabel('Количество вхождений')
#plt.show()
plt.savefig('/home/kprlns/Desktop/Mag1Cource/2sem/NLP/log10000.png')
