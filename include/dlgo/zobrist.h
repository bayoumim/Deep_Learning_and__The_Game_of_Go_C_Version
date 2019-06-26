#ifndef _ZOBRIST_H
#define _ZOBRIST_H
#include <map> 
#include "gotypes.h" 

std::map<Point , std::map<Color, unsigned long long int> >  HASH_CODE = {{ { 1 , 1 } , {{Color::black,606610977102444280},{Color::white,7068641224577739721}} },
{ { 1 , 2 } , {{Color::black,3130710918123035464},{Color::white,8443837270874830543}} },
{ { 1 , 3 } , {{Color::black,2442810971443284618},{Color::white,1768192591358509605}} },
{ { 1 , 4 } , {{Color::black,7778866119960641552},{Color::white,5035799209394608901}} },
{ { 1 , 5 } , {{Color::black,7845356865780460176},{Color::white,3394578529375205246}} },
{ { 1 , 6 } , {{Color::black,8100013667199103502},{Color::white,5750951782939772023}} },
{ { 1 , 7 } , {{Color::black,4946890478709497167},{Color::white,8146519254106984468}} },
{ { 1 , 8 } , {{Color::black,1267784028650215845},{Color::white,2243665409605238653}} },
{ { 1 , 9 } , {{Color::black,6082965761928602974},{Color::white,5839060909011179219}} },
{ { 1 , 10 } , {{Color::black,6383228978930403030},{Color::white,8951190098423387903}} },
{ { 1 , 11 } , {{Color::black,3174939682100485516},{Color::white,8006922303568942903}} },
{ { 1 , 12 } , {{Color::black,1412660102242170316},{Color::white,7337716249548679027}} },
{ { 1 , 13 } , {{Color::black,8492468853166292809},{Color::white,7089563237004867212}} },
{ { 1 , 14 } , {{Color::black,822391375953016378},{Color::white,8312129274921395408}} },
{ { 1 , 15 } , {{Color::black,6910519801985949262},{Color::white,3296017958836018093}} },
{ { 1 , 16 } , {{Color::black,1266314317995106769},{Color::white,4735631023582871807}} },
{ { 1 , 17 } , {{Color::black,1464392638680441747},{Color::white,5304984100488740493}} },
{ { 1 , 18 } , {{Color::black,6399753522467146730},{Color::white,2707920336177460720}} },
{ { 1 , 19 } , {{Color::black,9017731529548898233},{Color::white,4534694360466888079}} },
{ { 2 , 1 } , {{Color::black,2605135342334409322},{Color::white,6751649107896071679}} },
{ { 2 , 2 } , {{Color::black,921217480628232881},{Color::white,5196042699591652123}} },
{ { 2 , 3 } , {{Color::black,8315206509925701188},{Color::white,6407080718850720637}} },
{ { 2 , 4 } , {{Color::black,4158235061407409297},{Color::white,4369511529032623323}} },
{ { 2 , 5 } , {{Color::black,4084332202741104240},{Color::white,327722847878395167}} },
{ { 2 , 6 } , {{Color::black,623081983452894690},{Color::white,6223581617679142596}} },
{ { 2 , 7 } , {{Color::black,5604343971424918875},{Color::white,7380513414561559394}} },
{ { 2 , 8 } , {{Color::black,8414931412260563105},{Color::white,2478438772765901572}} },
{ { 2 , 9 } , {{Color::black,1909369363489887368},{Color::white,4086097308526041631}} },
{ { 2 , 10 } , {{Color::black,4912339681076633732},{Color::white,7690812214715899604}} },
{ { 2 , 11 } , {{Color::black,4227227713975138671},{Color::white,2076860972661306872}} },
{ { 2 , 12 } , {{Color::black,2056919996423689236},{Color::white,8676906223055842404}} },
{ { 2 , 13 } , {{Color::black,8331702148106347508},{Color::white,4607612295967880157}} },
{ { 2 , 14 } , {{Color::black,7454100367321226339},{Color::white,3566456674512202318}} },
{ { 2 , 15 } , {{Color::black,1926410617110661010},{Color::white,3523350494921620710}} },
{ { 2 , 16 } , {{Color::black,984810786624189050},{Color::white,9002747433184684976}} },
{ { 2 , 17 } , {{Color::black,5853219869128768609},{Color::white,3582661242628932665}} },
{ { 2 , 18 } , {{Color::black,5912900358431608545},{Color::white,884631307835887034}} },
{ { 2 , 19 } , {{Color::black,3780319357605628227},{Color::white,7383355914881349556}} },
{ { 3 , 1 } , {{Color::black,468719672356814248},{Color::white,7821453160644180875}} },
{ { 3 , 2 } , {{Color::black,2758787292493110547},{Color::white,3227416696815866587}} },
{ { 3 , 3 } , {{Color::black,7323306255218118943},{Color::white,2238167323110120155}} },
{ { 3 , 4 } , {{Color::black,2437498652327369238},{Color::white,7000924840119297283}} },
{ { 3 , 5 } , {{Color::black,1707367336136622188},{Color::white,6806369966377410137}} },
{ { 3 , 6 } , {{Color::black,360925341646759428},{Color::white,3098057574580544163}} },
{ { 3 , 7 } , {{Color::black,7971799008085281492},{Color::white,6996597837161277781}} },
{ { 3 , 8 } , {{Color::black,7404706160373826583},{Color::white,3090283418927670560}} },
{ { 3 , 9 } , {{Color::black,7022711028203766922},{Color::white,1264569188259366378}} },
{ { 3 , 10 } , {{Color::black,8844511495131255098},{Color::white,8379900790011467262}} },
{ { 3 , 11 } , {{Color::black,3260231199529853273},{Color::white,7297629326745173105}} },
{ { 3 , 12 } , {{Color::black,3476578280799996623},{Color::white,2285971600179534636}} },
{ { 3 , 13 } , {{Color::black,4165741432343778806},{Color::white,2696854951395123987}} },
{ { 3 , 14 } , {{Color::black,2508861932792817019},{Color::white,1779047497473930549}} },
{ { 3 , 15 } , {{Color::black,7882846423293419045},{Color::white,3762822954148810341}} },
{ { 3 , 16 } , {{Color::black,478680483838581848},{Color::white,325745843928742554}} },
{ { 3 , 17 } , {{Color::black,2203483485676692917},{Color::white,6670755742262248573}} },
{ { 3 , 18 } , {{Color::black,3844680238246032439},{Color::white,7753002646713345416}} },
{ { 3 , 19 } , {{Color::black,4551194474038478451},{Color::white,3948491524703157020}} },
{ { 4 , 1 } , {{Color::black,6869805918572656831},{Color::white,4775805315294824387}} },
{ { 4 , 2 } , {{Color::black,7443840078311252465},{Color::white,2549626608886823806}} },
{ { 4 , 3 } , {{Color::black,8476747616534034619},{Color::white,1159966303070226043}} },
{ { 4 , 4 } , {{Color::black,3507728133505236352},{Color::white,5827419818012350922}} },
{ { 4 , 5 } , {{Color::black,966435552966937744},{Color::white,4639722154390710319}} },
{ { 4 , 6 } , {{Color::black,6603511393435912318},{Color::white,2279301029977004980}} },
{ { 4 , 7 } , {{Color::black,8158598546868265127},{Color::white,1063325134076040684}} },
{ { 4 , 8 } , {{Color::black,7621373388864019526},{Color::white,5648398536608122926}} },
{ { 4 , 9 } , {{Color::black,5376891707894043796},{Color::white,219694276408912113}} },
{ { 4 , 10 } , {{Color::black,4377214739860531618},{Color::white,8826882251591415538}} },
{ { 4 , 11 } , {{Color::black,7940731333779876714},{Color::white,2036670901116042454}} },
{ { 4 , 12 } , {{Color::black,9118134301139302283},{Color::white,2056488529222640676}} },
{ { 4 , 13 } , {{Color::black,790347690609161765},{Color::white,324363895174646229}} },
{ { 4 , 14 } , {{Color::black,5349939288706975008},{Color::white,3881084466209981508}} },
{ { 4 , 15 } , {{Color::black,6120756755490164447},{Color::white,8632542314727367803}} },
{ { 4 , 16 } , {{Color::black,8924726622139474961},{Color::white,7099712171673834871}} },
{ { 4 , 17 } , {{Color::black,5720521989283974065},{Color::white,6790154001475775719}} },
{ { 4 , 18 } , {{Color::black,997904979509606115},{Color::white,7696075467741464840}} },
{ { 4 , 19 } , {{Color::black,3281511805877657222},{Color::white,4985258028897712786}} },
{ { 5 , 1 } , {{Color::black,3667916512398154235},{Color::white,1227257997839049589}} },
{ { 5 , 2 } , {{Color::black,5473263069226298335},{Color::white,3670236405597653711}} },
{ { 5 , 3 } , {{Color::black,2794687703965749486},{Color::white,5960456588461165649}} },
{ { 5 , 4 } , {{Color::black,191018056460618936},{Color::white,8896633096374130604}} },
{ { 5 , 5 } , {{Color::black,410406219564925005},{Color::white,3281543279644296390}} },
{ { 5 , 6 } , {{Color::black,1072713258726970444},{Color::white,8583212062490975646}} },
{ { 5 , 7 } , {{Color::black,4769604431358905332},{Color::white,3473400948652059254}} },
{ { 5 , 8 } , {{Color::black,2474299912322586206},{Color::white,9164917703738286500}} },
{ { 5 , 9 } , {{Color::black,684329971991471510},{Color::white,6770299674733919374}} },
{ { 5 , 10 } , {{Color::black,7253289833349365467},{Color::white,189423928219248046}} },
{ { 5 , 11 } , {{Color::black,445204207384948264},{Color::white,2589386615548852279}} },
{ { 5 , 12 } , {{Color::black,7722382281719814173},{Color::white,3094399844433753435}} },
{ { 5 , 13 } , {{Color::black,648912574173254490},{Color::white,1752969164658794504}} },
{ { 5 , 14 } , {{Color::black,121470367368258123},{Color::white,2720015462459581348}} },
{ { 5 , 15 } , {{Color::black,8445177579595126392},{Color::white,7949792473569314529}} },
{ { 5 , 16 } , {{Color::black,5356101670107255420},{Color::white,5871834336484001374}} },
{ { 5 , 17 } , {{Color::black,2530599447779519413},{Color::white,7327452752173045177}} },
{ { 5 , 18 } , {{Color::black,2316333339545977024},{Color::white,238040063539951883}} },
{ { 5 , 19 } , {{Color::black,161683438643390977},{Color::white,1766130542095900480}} },
{ { 6 , 1 } , {{Color::black,7429936050119939158},{Color::white,7609871032836973194}} },
{ { 6 , 2 } , {{Color::black,6856883102665890525},{Color::white,2792551928865088418}} },
{ { 6 , 3 } , {{Color::black,7367058783052576744},{Color::white,662626187794384387}} },
{ { 6 , 4 } , {{Color::black,3004580472623997992},{Color::white,1920653892103467745}} },
{ { 6 , 5 } , {{Color::black,5108543571023969995},{Color::white,2034976647813550892}} },
{ { 6 , 6 } , {{Color::black,3493910814939730632},{Color::white,256438273304549836}} },
{ { 6 , 7 } , {{Color::black,5545469277979623088},{Color::white,6305995609056331761}} },
{ { 6 , 8 } , {{Color::black,735931936107216441},{Color::white,2158736781097453354}} },
{ { 6 , 9 } , {{Color::black,7615252200817428560},{Color::white,3755833054923903685}} },
{ { 6 , 10 } , {{Color::black,4756510365175998188},{Color::white,8585215102736137237}} },
{ { 6 , 11 } , {{Color::black,8355892581060626816},{Color::white,8066507738059214894}} },
{ { 6 , 12 } , {{Color::black,5485824583214333756},{Color::white,3274820896698337203}} },
{ { 6 , 13 } , {{Color::black,5026060286249663879},{Color::white,5056384218870631202}} },
{ { 6 , 14 } , {{Color::black,8361202735496085572},{Color::white,5133132088284755978}} },
{ { 6 , 15 } , {{Color::black,7782579384469163666},{Color::white,660864082067579837}} },
{ { 6 , 16 } , {{Color::black,9112141887957375462},{Color::white,8574106963367264921}} },
{ { 6 , 17 } , {{Color::black,4950695454372365099},{Color::white,6690333346390698632}} },
{ { 6 , 18 } , {{Color::black,674208357823283723},{Color::white,4484755074954491057}} },
{ { 6 , 19 } , {{Color::black,4441792419261684798},{Color::white,597128222844053075}} },
{ { 7 , 1 } , {{Color::black,7266537709957217830},{Color::white,6607980039081310341}} },
{ { 7 , 2 } , {{Color::black,7379309362597505942},{Color::white,3090736599505782597}} },
{ { 7 , 3 } , {{Color::black,2212588292740342034},{Color::white,7585752642080390677}} },
{ { 7 , 4 } , {{Color::black,6261155924149978657},{Color::white,7810299208648161516}} },
{ { 7 , 5 } , {{Color::black,3075332016110353775},{Color::white,664739744855358717}} },
{ { 7 , 6 } , {{Color::black,4246576673730357820},{Color::white,6200206768889455405}} },
{ { 7 , 7 } , {{Color::black,3844523492187967969},{Color::white,4836263358676717457}} },
{ { 7 , 8 } , {{Color::black,5330522888847529847},{Color::white,4664861539877714856}} },
{ { 7 , 9 } , {{Color::black,5942869758055272839},{Color::white,2373128883182573253}} },
{ { 7 , 10 } , {{Color::black,6333501948067796428},{Color::white,933632822850417598}} },
{ { 7 , 11 } , {{Color::black,1648796178995355233},{Color::white,6313584748955177602}} },
{ { 7 , 12 } , {{Color::black,8967202366464537106},{Color::white,2051509064086955290}} },
{ { 7 , 13 } , {{Color::black,482287172194605672},{Color::white,9140511191435926785}} },
{ { 7 , 14 } , {{Color::black,3319467405348941145},{Color::white,7980283790965607290}} },
{ { 7 , 15 } , {{Color::black,7078367058707423708},{Color::white,4008422045336239293}} },
{ { 7 , 16 } , {{Color::black,8468787068579326075},{Color::white,2426584818799501168}} },
{ { 7 , 17 } , {{Color::black,5733379488964445570},{Color::white,5192913469306378307}} },
{ { 7 , 18 } , {{Color::black,3855355896793642379},{Color::white,8479408492002995500}} },
{ { 7 , 19 } , {{Color::black,8629773465083130535},{Color::white,185505384147852}} },
{ { 8 , 1 } , {{Color::black,6707914850995468002},{Color::white,1620512242954828372}} },
{ { 8 , 2 } , {{Color::black,7661972200613038405},{Color::white,3433254256615945436}} },
{ { 8 , 3 } , {{Color::black,5425279890336662589},{Color::white,4763888092245231185}} },
{ { 8 , 4 } , {{Color::black,7237302869306037157},{Color::white,7787266368633135458}} },
{ { 8 , 5 } , {{Color::black,5868106928537495802},{Color::white,4396145720865047500}} },
{ { 8 , 6 } , {{Color::black,4433841584451525173},{Color::white,32318425814325974}} },
{ { 8 , 7 } , {{Color::black,4427471387284890692},{Color::white,5243917796931005638}} },
{ { 8 , 8 } , {{Color::black,6940859490817757052},{Color::white,4164612564370584884}} },
{ { 8 , 9 } , {{Color::black,1783373166834168738},{Color::white,3358721097976632649}} },
{ { 8 , 10 } , {{Color::black,3913916419512666078},{Color::white,866899551214423066}} },
{ { 8 , 11 } , {{Color::black,7290934043107447131},{Color::white,1347030789721615359}} },
{ { 8 , 12 } , {{Color::black,3096062349089547845},{Color::white,6628101510584518980}} },
{ { 8 , 13 } , {{Color::black,783806492276438994},{Color::white,4605855254047126975}} },
{ { 8 , 14 } , {{Color::black,759081570081879357},{Color::white,4764227895536927087}} },
{ { 8 , 15 } , {{Color::black,1228031055052170947},{Color::white,1302637520766947342}} },
{ { 8 , 16 } , {{Color::black,4282077933588764943},{Color::white,7267337851446052424}} },
{ { 8 , 17 } , {{Color::black,3648491516094395715},{Color::white,3449398048322355430}} },
{ { 8 , 18 } , {{Color::black,6375254624695282149},{Color::white,82019349513925455}} },
{ { 8 , 19 } , {{Color::black,8956214772738609845},{Color::white,4983642451421817332}} },
{ { 9 , 1 } , {{Color::black,8380894264523584087},{Color::white,6236449683061859667}} },
{ { 9 , 2 } , {{Color::black,4238686346892961923},{Color::white,8552847254346385921}} },
{ { 9 , 3 } , {{Color::black,5192399450040415974},{Color::white,1207628447822141913}} },
{ { 9 , 4 } , {{Color::black,3461184894471929743},{Color::white,9053862904695274128}} },
{ { 9 , 5 } , {{Color::black,3154144447362617686},{Color::white,3731425043666210970}} },
{ { 9 , 6 } , {{Color::black,277911147515411328},{Color::white,3694734410009346650}} },
{ { 9 , 7 } , {{Color::black,7374981049664210110},{Color::white,4548799018888022911}} },
{ { 9 , 8 } , {{Color::black,4758514728281438827},{Color::white,3306296441469812977}} },
{ { 9 , 9 } , {{Color::black,1050368374777114260},{Color::white,6501396999559336036}} },
{ { 9 , 10 } , {{Color::black,2368095827173083252},{Color::white,6141860276803096757}} },
{ { 9 , 11 } , {{Color::black,7583409366895958937},{Color::white,4551925822497801643}} },
{ { 9 , 12 } , {{Color::black,7195727507495971546},{Color::white,2071139470956560519}} },
{ { 9 , 13 } , {{Color::black,7113988320891161277},{Color::white,5076586107823320138}} },
{ { 9 , 14 } , {{Color::black,7811855242378979833},{Color::white,5504663822999497478}} },
{ { 9 , 15 } , {{Color::black,6998673986911861304},{Color::white,2114370130410900272}} },
{ { 9 , 16 } , {{Color::black,1887462885315026581},{Color::white,1401641015422099810}} },
{ { 9 , 17 } , {{Color::black,7530599972797947985},{Color::white,2895192284257629360}} },
{ { 9 , 18 } , {{Color::black,6881591948672059004},{Color::white,3956478669450975969}} },
{ { 9 , 19 } , {{Color::black,6396007182156647510},{Color::white,2106982542019587099}} },
{ { 10 , 1 } , {{Color::black,4436075906200473958},{Color::white,8285284512079535963}} },
{ { 10 , 2 } , {{Color::black,7115022250016828522},{Color::white,2654597474721120662}} },
{ { 10 , 3 } , {{Color::black,5288088668591243716},{Color::white,5747546338998716088}} },
{ { 10 , 4 } , {{Color::black,7741680785951890087},{Color::white,670540867286917304}} },
{ { 10 , 5 } , {{Color::black,6469197794380175616},{Color::white,6890395744892195211}} },
{ { 10 , 6 } , {{Color::black,182914583760744624},{Color::white,4723135697706315105}} },
{ { 10 , 7 } , {{Color::black,6566327582004965224},{Color::white,6346957129336895046}} },
{ { 10 , 8 } , {{Color::black,6540134886200705117},{Color::white,3159764700863506448}} },
{ { 10 , 9 } , {{Color::black,5119581216542955327},{Color::white,7833891970751332782}} },
{ { 10 , 10 } , {{Color::black,4885375759877138676},{Color::white,5184846203464141575}} },
{ { 10 , 11 } , {{Color::black,3063753247722188797},{Color::white,641877800778898752}} },
{ { 10 , 12 } , {{Color::black,5913247815414918939},{Color::white,8606047244416807131}} },
{ { 10 , 13 } , {{Color::black,8112861518160056484},{Color::white,3173033403930752005}} },
{ { 10 , 14 } , {{Color::black,17609385603167475},{Color::white,913355917411904466}} },
{ { 10 , 15 } , {{Color::black,2153506951768938610},{Color::white,4014185006684748070}} },
{ { 10 , 16 } , {{Color::black,3007032750636423106},{Color::white,785585241131771100}} },
{ { 10 , 17 } , {{Color::black,503057425059720559},{Color::white,9056609781114876300}} },
{ { 10 , 18 } , {{Color::black,138536115379198683},{Color::white,5407552941968696082}} },
{ { 10 , 19 } , {{Color::black,7143070493587620921},{Color::white,2365627387072232054}} },
{ { 11 , 1 } , {{Color::black,1389914080240163291},{Color::white,3384566373305090063}} },
{ { 11 , 2 } , {{Color::black,7878968516367666780},{Color::white,7035404974249754753}} },
{ { 11 , 3 } , {{Color::black,8218625601941727462},{Color::white,853014186949546782}} },
{ { 11 , 4 } , {{Color::black,7587818331356267637},{Color::white,850187569543123814}} },
{ { 11 , 5 } , {{Color::black,5360752498953600504},{Color::white,4755512683710493936}} },
{ { 11 , 6 } , {{Color::black,9156184762148113381},{Color::white,6037243387763502409}} },
{ { 11 , 7 } , {{Color::black,1485655891077085003},{Color::white,7389354317442039794}} },
{ { 11 , 8 } , {{Color::black,4972384783743903079},{Color::white,5939257995155678576}} },
{ { 11 , 9 } , {{Color::black,7649007001637331691},{Color::white,4485768315060794100}} },
{ { 11 , 10 } , {{Color::black,4406537535687765812},{Color::white,4544766607894679108}} },
{ { 11 , 11 } , {{Color::black,4431626736236684192},{Color::white,467906145497656105}} },
{ { 11 , 12 } , {{Color::black,5732375536797618558},{Color::white,8680586332304853845}} },
{ { 11 , 13 } , {{Color::black,4603800370993546317},{Color::white,5992899421124234366}} },
{ { 11 , 14 } , {{Color::black,7570843553612016610},{Color::white,838775152982549575}} },
{ { 11 , 15 } , {{Color::black,8905050726915274286},{Color::white,2901401466135282001}} },
{ { 11 , 16 } , {{Color::black,8442470870024013938},{Color::white,4497749409068843622}} },
{ { 11 , 17 } , {{Color::black,6343083573247043753},{Color::white,1054098821436744021}} },
{ { 11 , 18 } , {{Color::black,3583206518763988413},{Color::white,7781379391280949578}} },
{ { 11 , 19 } , {{Color::black,8812253173559607688},{Color::white,5388459582012410705}} },
{ { 12 , 1 } , {{Color::black,2528887808313360363},{Color::white,3720255043399306342}} },
{ { 12 , 2 } , {{Color::black,6159393333797646447},{Color::white,7410380726308688974}} },
{ { 12 , 3 } , {{Color::black,3777915930933491151},{Color::white,9083637491667827268}} },
{ { 12 , 4 } , {{Color::black,6487488463764588688},{Color::white,6488869244278438581}} },
{ { 12 , 5 } , {{Color::black,6001938643524048863},{Color::white,5365930326558645853}} },
{ { 12 , 6 } , {{Color::black,2776264467230855465},{Color::white,2513439677903745607}} },
{ { 12 , 7 } , {{Color::black,6379717970309562168},{Color::white,6496355370728037659}} },
{ { 12 , 8 } , {{Color::black,4663074673470687216},{Color::white,8051055394253711352}} },
{ { 12 , 9 } , {{Color::black,5850318183696510573},{Color::white,1633944557639103446}} },
{ { 12 , 10 } , {{Color::black,883926455237169762},{Color::white,7054332813461107896}} },
{ { 12 , 11 } , {{Color::black,6359308076610496105},{Color::white,5224185587802425944}} },
{ { 12 , 12 } , {{Color::black,6240193650384341516},{Color::white,8308548234163264957}} },
{ { 12 , 13 } , {{Color::black,2659272589650088723},{Color::white,2336025946618702945}} },
{ { 12 , 14 } , {{Color::black,797485335717734368},{Color::white,5830849477168531691}} },
{ { 12 , 15 } , {{Color::black,2535568160380436628},{Color::white,6855201659203601108}} },
{ { 12 , 16 } , {{Color::black,4222863153381696652},{Color::white,9213603851868775849}} },
{ { 12 , 17 } , {{Color::black,8330342011514352304},{Color::white,2515376070472331537}} },
{ { 12 , 18 } , {{Color::black,9081424543990887192},{Color::white,2600355060013240139}} },
{ { 12 , 19 } , {{Color::black,1411460184216472083},{Color::white,2405332273840133376}} },
{ { 13 , 1 } , {{Color::black,5553175798105729456},{Color::white,1294904320095212902}} },
{ { 13 , 2 } , {{Color::black,1139205101919520551},{Color::white,6418513141525498218}} },
{ { 13 , 3 } , {{Color::black,2751804926699793015},{Color::white,8155277512580014810}} },
{ { 13 , 4 } , {{Color::black,6548830549330514609},{Color::white,7797311944105283421}} },
{ { 13 , 5 } , {{Color::black,5971179047486147818},{Color::white,8755927893867243917}} },
{ { 13 , 6 } , {{Color::black,2139973781873388844},{Color::white,5035225289898511039}} },
{ { 13 , 7 } , {{Color::black,272998742376371773},{Color::white,3603369458500961288}} },
{ { 13 , 8 } , {{Color::black,3404173323027247173},{Color::white,8808197644723870534}} },
{ { 13 , 9 } , {{Color::black,6797265932413924100},{Color::white,8751923387494769590}} },
{ { 13 , 10 } , {{Color::black,1828477513991367274},{Color::white,6542474209984303337}} },
{ { 13 , 11 } , {{Color::black,8033566769043534232},{Color::white,3598135933324166931}} },
{ { 13 , 12 } , {{Color::black,3632657436903334187},{Color::white,1959655427375451636}} },
{ { 13 , 13 } , {{Color::black,8968855452183344658},{Color::white,5749812005664276861}} },
{ { 13 , 14 } , {{Color::black,1054235207043030404},{Color::white,5587530432309696800}} },
{ { 13 , 15 } , {{Color::black,1669694538852510188},{Color::white,1785138072901564000}} },
{ { 13 , 16 } , {{Color::black,6525998794815422918},{Color::white,7690072836752382645}} },
{ { 13 , 17 } , {{Color::black,5212024548288884581},{Color::white,2081989714848498000}} },
{ { 13 , 18 } , {{Color::black,673273737708565010},{Color::white,7798206481124046889}} },
{ { 13 , 19 } , {{Color::black,3378514976875721144},{Color::white,94346298469964239}} },
{ { 14 , 1 } , {{Color::black,5860075435757821950},{Color::white,7534073522568387168}} },
{ { 14 , 2 } , {{Color::black,3344554147009857646},{Color::white,7093578764349666335}} },
{ { 14 , 3 } , {{Color::black,6621331783843589761},{Color::white,1521395912183373925}} },
{ { 14 , 4 } , {{Color::black,7123395878273690234},{Color::white,3517428781749624361}} },
{ { 14 , 5 } , {{Color::black,2169014877181166698},{Color::white,6310399275633022910}} },
{ { 14 , 6 } , {{Color::black,5450925179685417572},{Color::white,6230241903501986029}} },
{ { 14 , 7 } , {{Color::black,1096411147419817419},{Color::white,3482427341884167529}} },
{ { 14 , 8 } , {{Color::black,4181447333675302123},{Color::white,8967867365749847604}} },
{ { 14 , 9 } , {{Color::black,5586330430531497706},{Color::white,7570758836866646213}} },
{ { 14 , 10 } , {{Color::black,1418209187578046658},{Color::white,5580295093110516321}} },
{ { 14 , 11 } , {{Color::black,3553737802428473322},{Color::white,1634536952081598467}} },
{ { 14 , 12 } , {{Color::black,7829836298033065277},{Color::white,2379672089428219579}} },
{ { 14 , 13 } , {{Color::black,57468581016119112},{Color::white,7226788193834902262}} },
{ { 14 , 14 } , {{Color::black,2355766896074126349},{Color::white,7124991825447944815}} },
{ { 14 , 15 } , {{Color::black,3346339866651643384},{Color::white,7322401667897252241}} },
{ { 14 , 16 } , {{Color::black,6498524182975667679},{Color::white,3197210999127340085}} },
{ { 14 , 17 } , {{Color::black,4367407807523723733},{Color::white,3023192461763691189}} },
{ { 14 , 18 } , {{Color::black,6647235271466826646},{Color::white,1766979083949944788}} },
{ { 14 , 19 } , {{Color::black,5575000136535746640},{Color::white,6928127007876156942}} },
{ { 15 , 1 } , {{Color::black,8362067321326031049},{Color::white,5146400366146911841}} },
{ { 15 , 2 } , {{Color::black,7146648283030048724},{Color::white,7517809453656605550}} },
{ { 15 , 3 } , {{Color::black,6014285800459350377},{Color::white,8303388881504633573}} },
{ { 15 , 4 } , {{Color::black,5690871426905083034},{Color::white,8632152867667699900}} },
{ { 15 , 5 } , {{Color::black,7722780273683801369},{Color::white,6258804789113872131}} },
{ { 15 , 6 } , {{Color::black,4850912251695188332},{Color::white,4261249477018872397}} },
{ { 15 , 7 } , {{Color::black,3677277080323271099},{Color::white,2523469701177612944}} },
{ { 15 , 8 } , {{Color::black,1438789247065524794},{Color::white,3005076976876248851}} },
{ { 15 , 9 } , {{Color::black,480065729005873528},{Color::white,5722935292310677682}} },
{ { 15 , 10 } , {{Color::black,1738428552908164795},{Color::white,8291009419720017580}} },
{ { 15 , 11 } , {{Color::black,5344273954876560064},{Color::white,3643960696015882436}} },
{ { 15 , 12 } , {{Color::black,1096927299153729581},{Color::white,3004124869665358165}} },
{ { 15 , 13 } , {{Color::black,1461960364634736328},{Color::white,5631851459349109091}} },
{ { 15 , 14 } , {{Color::black,3625879060030580284},{Color::white,6385397784735531691}} },
{ { 15 , 15 } , {{Color::black,4723714876431022364},{Color::white,8922905234662648540}} },
{ { 15 , 16 } , {{Color::black,8695264600982038113},{Color::white,1438692860802692795}} },
{ { 15 , 17 } , {{Color::black,8383796682253513402},{Color::white,5496646535935320221}} },
{ { 15 , 18 } , {{Color::black,8732897091830147756},{Color::white,641347797667064740}} },
{ { 15 , 19 } , {{Color::black,3196949691272202239},{Color::white,1662600754293189657}} },
{ { 16 , 1 } , {{Color::black,2631787474385617861},{Color::white,8608541634913132381}} },
{ { 16 , 2 } , {{Color::black,8278043363891613313},{Color::white,2665520737923477855}} },
{ { 16 , 3 } , {{Color::black,272933862092685737},{Color::white,1998529676000585311}} },
{ { 16 , 4 } , {{Color::black,2505183500741642565},{Color::white,4643784598177889327}} },
{ { 16 , 5 } , {{Color::black,7578022596086821694},{Color::white,1315202163663142784}} },
{ { 16 , 6 } , {{Color::black,8894965792054823739},{Color::white,8635131923246295426}} },
{ { 16 , 7 } , {{Color::black,2632945129602384248},{Color::white,3715830028520611920}} },
{ { 16 , 8 } , {{Color::black,8043306022903565822},{Color::white,6935091893015770248}} },
{ { 16 , 9 } , {{Color::black,5847654327496920928},{Color::white,9012903012220054217}} },
{ { 16 , 10 } , {{Color::black,5415015821725891435},{Color::white,8792467796614812620}} },
{ { 16 , 11 } , {{Color::black,8038821614604825973},{Color::white,6365581767254256413}} },
{ { 16 , 12 } , {{Color::black,481496977927869374},{Color::white,6230630040586394408}} },
{ { 16 , 13 } , {{Color::black,446714883758715574},{Color::white,3245964374759493793}} },
{ { 16 , 14 } , {{Color::black,2672821775604016963},{Color::white,7330897461012383764}} },
{ { 16 , 15 } , {{Color::black,4909749185640035826},{Color::white,5795747699639409340}} },
{ { 16 , 16 } , {{Color::black,618489094168788352},{Color::white,7280865130747859611}} },
{ { 16 , 17 } , {{Color::black,6230844004646528610},{Color::white,3928859981805812154}} },
{ { 16 , 18 } , {{Color::black,5179245148617302633},{Color::white,1829125799280668879}} },
{ { 16 , 19 } , {{Color::black,6555929588823443631},{Color::white,2183209509428797677}} },
{ { 17 , 1 } , {{Color::black,711943574355562621},{Color::white,6851015908087894487}} },
{ { 17 , 2 } , {{Color::black,1583175855911696534},{Color::white,1877326917253794136}} },
{ { 17 , 3 } , {{Color::black,2705930234622545260},{Color::white,8408337769819277621}} },
{ { 17 , 4 } , {{Color::black,6380067360043280262},{Color::white,589270580963551838}} },
{ { 17 , 5 } , {{Color::black,7848017698299411997},{Color::white,3551472230252932481}} },
{ { 17 , 6 } , {{Color::black,4847695899464036759},{Color::white,760005957356922719}} },
{ { 17 , 7 } , {{Color::black,5903474459247693709},{Color::white,599683303850680558}} },
{ { 17 , 8 } , {{Color::black,1379989355356007903},{Color::white,2355136394236092843}} },
{ { 17 , 9 } , {{Color::black,1042867284544341872},{Color::white,916382647500556592}} },
{ { 17 , 10 } , {{Color::black,379767139104962673},{Color::white,856712285809869810}} },
{ { 17 , 11 } , {{Color::black,1699982290385845367},{Color::white,3067878269672585031}} },
{ { 17 , 12 } , {{Color::black,3521593880353474481},{Color::white,4071475190543218760}} },
{ { 17 , 13 } , {{Color::black,4043049538800281170},{Color::white,2629469636344035100}} },
{ { 17 , 14 } , {{Color::black,6096288377994737902},{Color::white,4451760826452571465}} },
{ { 17 , 15 } , {{Color::black,2969912788688961414},{Color::white,6901238850492643726}} },
{ { 17 , 16 } , {{Color::black,6183501339242038256},{Color::white,7511098128190478860}} },
{ { 17 , 17 } , {{Color::black,3993896663658822260},{Color::white,6424216969301533187}} },
{ { 17 , 18 } , {{Color::black,7489052214958705236},{Color::white,8942607073839821908}} },
{ { 17 , 19 } , {{Color::black,7222489290920310265},{Color::white,274429651993312851}} },
{ { 18 , 1 } , {{Color::black,7930445240404476398},{Color::white,2819280612864945048}} },
{ { 18 , 2 } , {{Color::black,9205198485702702444},{Color::white,8174657215951719107}} },
{ { 18 , 3 } , {{Color::black,2150664539496667021},{Color::white,5325434955611463884}} },
{ { 18 , 4 } , {{Color::black,8462923702994637736},{Color::white,2672790600339940762}} },
{ { 18 , 5 } , {{Color::black,2154453750358709480},{Color::white,6613730620089707573}} },
{ { 18 , 6 } , {{Color::black,4200456996948915472},{Color::white,7449751309533554527}} },
{ { 18 , 7 } , {{Color::black,4344699373222145567},{Color::white,8767194662652077984}} },
{ { 18 , 8 } , {{Color::black,1271526887862463946},{Color::white,269150543971886310}} },
{ { 18 , 9 } , {{Color::black,2467305305776686574},{Color::white,1344341049699065705}} },
{ { 18 , 10 } , {{Color::black,4429338329688826602},{Color::white,6672246610091820605}} },
{ { 18 , 11 } , {{Color::black,6326817152822266100},{Color::white,6546976427504299915}} },
{ { 18 , 12 } , {{Color::black,3764109440065269457},{Color::white,7026919821999351039}} },
{ { 18 , 13 } , {{Color::black,8042024450468143170},{Color::white,2670745131928346056}} },
{ { 18 , 14 } , {{Color::black,2217075327432119096},{Color::white,914563871384297825}} },
{ { 18 , 15 } , {{Color::black,4611714904456065237},{Color::white,8835744215008821703}} },
{ { 18 , 16 } , {{Color::black,3706090059542929481},{Color::white,1862912254257249230}} },
{ { 18 , 17 } , {{Color::black,5544718898371285410},{Color::white,9159325586788332944}} },
{ { 18 , 18 } , {{Color::black,1979096057482507996},{Color::white,1243800685607120686}} },
{ { 18 , 19 } , {{Color::black,1630836055028201986},{Color::white,3169822948735844370}} },
{ { 19 , 1 } , {{Color::black,630980137929441772},{Color::white,1840338249189027958}} },
{ { 19 , 2 } , {{Color::black,906894034860929603},{Color::white,3845878118293800775}} },
{ { 19 , 3 } , {{Color::black,2855196776253406742},{Color::white,9009994390361332991}} },
{ { 19 , 4 } , {{Color::black,5287035708316561985},{Color::white,7276806161616396751}} },
{ { 19 , 5 } , {{Color::black,4397664489020521714},{Color::white,6985170937857665316}} },
{ { 19 , 6 } , {{Color::black,6122010002394612029},{Color::white,8422131730022356060}} },
{ { 19 , 7 } , {{Color::black,4226582868981579578},{Color::white,2937941660942929118}} },
{ { 19 , 8 } , {{Color::black,2817451318291467487},{Color::white,9033594340148520448}} },
{ { 19 , 9 } , {{Color::black,5474692091190341226},{Color::white,6153769358678472636}} },
{ { 19 , 10 } , {{Color::black,8132935355955717130},{Color::white,8447610094160899353}} },
{ { 19 , 11 } , {{Color::black,134826295461419987},{Color::white,1595922630468828165}} },
{ { 19 , 12 } , {{Color::black,3744706148548589408},{Color::white,4190000776440111237}} },
{ { 19 , 13 } , {{Color::black,5682225884288329303},{Color::white,844867371248046377}} },
{ { 19 , 14 } , {{Color::black,9136528005447949842},{Color::white,6241392962814912003}} },
{ { 19 , 15 } , {{Color::black,1275810964433928431},{Color::white,9199361787778639459}} },
{ { 19 , 16 } , {{Color::black,1246751477932254279},{Color::white,4421222128753767359}} },
{ { 19 , 17 } , {{Color::black,8930546681230028102},{Color::white,1762184905153361048}} },
{ { 19 , 18 } , {{Color::black,1311941491317625391},{Color::white,5678517941285946529}} },
{ { 19 , 19 } , {{Color::black,146005817745350023},{Color::white,5519686587256867453}} }};

unsigned long long int EMPTY_BOARD = 2816497798025261921;

#endif
