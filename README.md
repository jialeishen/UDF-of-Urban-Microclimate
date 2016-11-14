# 城市微气候

##1. 绪论
在使用商业CFD软件ANSYS Fluent®研究城市微气候（Urban Microclimate）时，常常需要根据城市微气候的各特点编写用户自定义函数（UDF, i.e. User Defined Function）来模拟真实的城市环境，本文档包含了其中一些常用的UDF。本文首先对UDF及城市微气候的基本概念各自进行了简单的介绍；并结合城市微气候中的概念对本文档中的UDF进行了简单介绍，目前本文档中的UDF主要针对城市风环境；最后推荐了一些城市微气候相关的书籍及论文文献。希望本文档中所讨论的内容能对大家今后的科研有所帮助。

##2. UDF简介
本文重点讨论的是有关城市微气候的内容，涉及UDF语法、C语言编程等内容不在本文的重点讨论范围内，相关资料可以在网上搜索到很多，这里只对UDF进行简单的介绍，以下内容引用自[流沙CAE的博客](http://blog.sina.com.cn/s/blog_599d8faa0102v3j7.html)：
>1、什么是UDF
>
>UDF（User Defined Function，用户自定义函数），可以用于被ANSYS FLUENT求解器动态加载以增强其标准功能的C语言程序。UDF归根结底是一段C语言代码，但是需要在FLUENT规定的框架范围内去定义，这样才能够被FLUENT认可并在其加载后以提供标准程序所不具备的功能。
>
>2、干嘛要用UDF
>
>在FLUENT中，可以利用UDF来延伸fluent自身的功能。比如说以下一些典型的应用：
>
>（1）自定义属性。如边界条件、材料属性、化学反应速率、输运方程源、UDS等；
>
>（2）迭代中调整计算中；
>
>（3）初始化；
>
>（4）异步执行命令；
>
>（5）迭代完后执行命令；
>
>（6）增强后处理；
>
>（7）增强现有的模型（如离散相模型、多相流模型等等）
>
>当然了，FLUENT本身已经具备了较多强大的功能，并不是所有的计算模型都需要使用UDF。
>
>3、UDF具有的特征
>
>虽然说UDF是利用C程序，但是毕竟是需要存在于FLUENT所订立的规则之下，因此其具有其特殊的特征：
>
>（1）UDF是利用的C程序语言，故源文件的扩展名为.c，可以用文本编辑器进行编辑。另外，UDF程序必须符合C语言语法要求；
>
>（2）UDF程序都是利用FLUENT提供的DEFINE宏进行定义；
>
>（3）所有的UDF程序都需要包含udf.h头文件；
>
>（4）UDF程序可以通过两种方式进行加载：解释与编译；解释型的UDF不需要外部编译器，而编译型*（本文作者注：原文此处为“解释型”，此处正确应为“编译型”）*的UDF则需要C编译器，在windows环境中常使用Visual studio，而在Linux环境中，则通常使用GCC。
>
>4、UDF的一些限制条件
>
>UDF不是万能的，虽然说在很多地方可以应用UDF以增强FLUENT自身的能力，但是毕竟局限于FLUENT的圈圈之类，还是存在一些局限性：
>
>（1）UDF中使用的物理量以及返回值均采用SI单位制；
>
>（2）若更换FLUENT运行环境（如FLUENT版本、操作系统环境等），则UDF需要重新进行编译加载。
>
>5、UDF如何学习
>
>UDF需要学习么？需要么，好像不需要。真的不需要么，个人觉得还是有必要的。
>
>UDF利用的是C语言，所以了解基本的C语言语法是必要的。
>
>那么C语法中有哪些是UDF中用得到的呢：首先，基本的赋值、条件判断、循环结构必须要清楚；其次掌握一些函数定义方面的基础；另外掌握宏定义有助于理解UDF的运作方式。个人觉得FLUENT附录中的C语言基础应该多看看，对于无编程经验的童鞋很重要。
>
>UDF手册比较完善，在使用UDF之前，建议先查一查手册，对着手册上的例子先模仿一番，然后在实例的基础上进行修改。
>
>熟悉FLUENT的内部运行规则，对于用好UDF是非常重要的。

通过上文的介绍，大家应该对UDF已经有了一个大概的印象，知道了UDF是什么、有什么用等等，这有助于大家进一步理解并学习UDF，更多的有关UDF具体编写及语法等内容，大家可以查阅Fluent的Help文档（即上文提到的手册）。

##3. 城市微气候简介
微气候是指在特定环境下不同于周围环境的当地小气候。而在城市尺度内，大气环境由于受到地形、植被绿化、水体、城市下垫面特征、城市布局形式、建筑物特征等因素的影响，常常表现出不同于周围大气环境的气候特点，这种现象也常被称为城市微气候。城市微气候常与城市环境中行人的健康、舒适性等直接相关，并间接影响室内环境。常见的如城市热岛现象（UHI, i.e. Urban Heat Island）、城市大气污染、建筑屋顶绿化、通风廊道等概念都属于城市微气候的研究范畴，涉及建筑、大气、环境、城市设计、城市规划等相关学科与领域。

城市微气候主要包括：**城市热环境、城市湿环境、城市风环境、城市大气环境、城市光环境、城市声环境**等。由于本文作者的研究方向及个人水平的限制，目前本文所涉及到的城市微气候内容只局限在对**城市风环境**的讨论，不过作者目前及未来的研究方向也包括了对城市大气环境（主要是气态污染物，e.g. NOx、CO、臭氧等，但不包括颗粒物）的研究，因此未来或许能在**城市大气环境**中增加一些内容。而对于**城市热环境**、**城市湿环境**等其他方向，作者目前及在可预见的未来都无法对其进行更多的研究并编写相关的UDF，因此希望能有更多同学对此进行研究并扩展相应的UDF，使之能应用到更为广泛的研究中。

下图摘自荷兰埃因霍温理工大学（TU/e）Bert Blocken教授的[一篇文章](http://www.sciencedirect.com/science/article/pii/S0360132315000724)，描述了城市物理环境所涉及到的内容。
![urbanphysics](https://github.com/kidisgod/UDF-of-Urban-Microclimate/blob/master/urbanphysics.png)

##4. 城市微气候相关UDF
###4.1 城市风环境
城市风环境对于整个城市环境有巨大影响，涉及城市空气污染、自然通风、对流热交换、风荷载及城市风害等内容，同时城市风环境作为室内环境的边界条件也对室内环境有着重要影响。不同的城市密度、城市建筑高度变化、城市及街道形态等的变化都会影响一定尺度下的城市风环境。除了这一系列的城市、街道、建筑的形态会对城市风环境产生重要影响之外，城市区域的入口边界条件（inlet flow）、植被等也会影响城市内部的风环境。

- **入口边界条件**

|相关UDF|
|---|
|**udf_of_inlet.c**|

入流边界条件，包括速度项、湍动能项、湍流耗散率项。这里速度项以指数分布为例，可以根据具体要求进行修改。

![inletflow](https://github.com/kidisgod/UDF-of-Urban-Microclimate/blob/master/inletflow.png)

- **植被对风场的影响**

|相关UDF|
|---|
|**udf_of_tree.c**|

植被对流场的影响，包括速度源项、湍动能源项、湍流耗散率源项。

- **通风评价指标**

 相关UDF：**udf_of_source_particular_area.c**

污染物源项，在特定区域内设定污染物源项。

-- **udf_of_urban_ventilation_indices.c**

城市通风评价指标，包括Purging flow rate，Local mean age of air，Mean residence time，Visitation frequency，Average residence time，Flow rate，Turn-over time，Air change rate，Air exchange efficiency

###4.2 城市大气环境
Loading...

##5. 更多阅读

限于篇幅，本文档对于城市微气候的介绍十分有限，如果有兴趣继续了解更多城市微气候相关的内容，以下是一些个人推荐的书籍与综述性论文，供大家参考学习：
  
###5.1 参考书：

（1）[城市环境物理](https://www.amazon.cn/%E5%9F%8E%E5%B8%82%E7%8E%AF%E5%A2%83%E7%89%A9%E7%90%86-%E5%88%98%E5%8A%A0%E5%B9%B3/dp/B004X8RC6A/ref=sr_1_1?ie=UTF8&qid=1478336099&sr=8-1&keywords=%E5%9F%8E%E5%B8%82%E7%8E%AF%E5%A2%83%E7%89%A9%E7%90%86)

强烈推荐，本文有大量内容直接摘自《城市环境物理》的各个章节或受其启发。

（2）[CFD与建筑环境设计](https://www.amazon.cn/CFD%E4%B8%8E%E5%BB%BA%E7%AD%91%E7%8E%AF%E5%A2%83%E8%AE%BE%E8%AE%A1-%E6%9D%91%E4%B8%8A%E5%91%A8%E4%B8%89/dp/B0012782NW/ref=sr_1_1?ie=UTF8&qid=1478336169&sr=8-1&keywords=CFD%E4%B8%8E%E5%BB%BA%E7%AD%91%E7%8E%AF%E5%A2%83%E8%AE%BE%E8%AE%A1)

本书的大部分内容介绍的是室内环境，大家可以只看其室外环境部分

（3）[Urban Microclimate: Designing the Spaces Between Buildings](https://www.amazon.cn/Urban-Microclimate-Designing-the-Spaces-Between-Buildings-Erell-Evyatar/dp/B008FYSNL6/ref=sr_1_1?ie=UTF8&qid=1478336175&sr=8-1&keywords=Urban+Microclimate%3A+Designing+the+Spaces+Between+Buildings)

本书有[中文翻译版](https://www.amazon.cn/%E5%9F%8E%E5%B8%82%E5%B0%8F%E6%B0%94%E5%80%99-%E5%BB%BA%E7%AD%91%E4%B9%8B%E9%97%B4%E7%9A%84%E7%A9%BA%E9%97%B4%E8%AE%BE%E8%AE%A1-%E5%9F%83%E7%BB%B4%E7%89%B9%C2%B7%E5%9F%83%E9%9B%B7%E5%B0%94/dp/B00JL2FMZQ/ref=sr_1_3?ie=UTF8&qid=1478336175&sr=8-3&keywords=Urban+Microclimate%3A+Designing+the+Spaces+Between+Buildings)，但是翻译的质量太差，**强烈不建议**大家阅读中文翻译版

*注：第三本英文书[图书馆](http://lib.nju.edu.cn/html/index.html)没有馆藏，但丁老师工作室有其影印版。其中文翻译版及另外两本中文书籍图书馆均有馆藏*

###5.2 综述性论文：

（1）[城市形态与城市微气候的关联性研究](http://www.cnki.net/KCMS/detail/detail.aspx?QueryID=3&CurRec=1&recid=&filename=JZXB201207005&dbname=CJFD2012&dbcode=CJFQ&pr=&urlid=&yx=&uid=WEEvREcwSlJHSldRa1FhcEE0L01SOC9Bb2NIa3FuWWNUc3RjVndKTjBhaz0=$9A4hF_YAuvQ5obgVAqNKPCYcEjKensW4ggI8Fm4gTkoUKaID8j8gFw!!&v=MzE3NDc0SDlQTXFJOUZZWVI4ZVgxTHV4WVM3RGgxVDNxVHJXTTFGckNVUkx5ZVp1WnFGeTdrVWJ2TUx6ZlRiTEc=)

（2）[AIJ guidelines for practical applications of CFD to pedestrian wind environment around buildings](http://www.sciencedirect.com/science/article/pii/S0167610508000445)

（3）[Thermal comfort: A review paper](http://www.sciencedirect.com/science/article/pii/S1364032110002200)

（4）[Modelling air qualityin street canyons: a review](http://www.sciencedirect.com/science/article/pii/S1352231002008579)

（5）[Urban Physics:Effect of the micro-climate on comfort,health and energy demand](http://www.sciencedirect.com/science/article/pii/S2095263512000301)

（6）[Approaches to study Urban Heat Island-Abilities and limitations](http://www.sciencedirect.com/science/article/pii/S0360132310001083)

（7）[A review on the generation, determination and mitigation of Urban Heat Island](http://www.sciencedirect.com/science/article/pii/S1001074208600194)

（8）[Cooling the cities – A review of reflective and green roof mitigation technologies to fight heat island and improve comfort in urban environments](http://www.sciencedirect.com/science/article/pii/S0038092X12002447)

（9）[Computational Fluid Dynamics for urban physics: Importance, scales, possibilities, limitations and ten tips and tricks towards accurate and reliable simulations](http://www.sciencedirect.com/science/article/pii/S0360132315000724)

（10）[Application of computational fluid dynamics in building performance simulation for the outdoor environment: an overview](http://china.tandfonline.com/doi/abs/10.1080/19401493.2010.513740)

 *注：这里只推荐了几篇综述性论文，还有大量相关研究论文，请大家自行[查阅](http://www.sciencedirect.com/)*

本文档介绍了几个常用的城市微气候的UDF，同时简单介绍了城市微气候相关内容，希望这些UDF和介绍内容可以在大家日后的科研中对大家有所帮助，同时**强烈邀请**大家对本文档内容进行修改及补充！！也欢迎大家上传更多相关的UDF。作者联系邮箱：shenjialei1992@163.com
