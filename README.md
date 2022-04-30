![urban](https://github.com/kidisgod/UDF-of-Urban-Microclimate/blob/master/urban.png)
# Urban Microclimate 城市微气候

## 0. Table of Content 目录
1. [Introduction 绪论](#1-introduction-绪论)
2. [Introduction of UDF UDF简介](#2-introduction-of-udf-udf简介)
3. [Introduction of Urban Microclimate 城市微气候简介](#3-introduction-of-urban-microclimate-城市微气候简介)
4. [UDFs in Urban Microclimate 城市微气候相关UDF](#4-UDFs-in-Urban-Microclimate-城市微气候相关UDF)
5. [Tutorials of Application of UDFs in Fluent 相关UDF解释与教程](#5-Tutorials-of-Application-of-UDFs-in-Fluent-相关UDF解释与教程)
6. [More Information 更多阅读](#6-More-Information-更多阅读)

## 1. Introduction 绪论
When using ANSYS Fluent® for urban microclimate simulation, it commonly requires users to apply some user defined functions (UDFs) to simulate the realistic urban environment and further solve specific urban microclimate problems, such as pollutant transmission, in ANSYS Fluent. This repo contains some commonly used UDF files of ANSYS Fluent for urban microclimate simulations. It includes the UDF files of wind velocity profile (inlet profile), pollutant emission source, tree and greening, and some commonly used performance indices for evaluating the urban ventilation. Some relevant publications are presented at the end of this document.

在使用商用CFD软件ANSYS Fluent®研究城市微气候（Urban Microclimate）时，常常需要根据城市微气候的各特点编写用户自定义函数（UDF, i.e. User Defined Function）来模拟真实的城市环境，本文档包含了其中一些常用的UDF。本文首先对UDF及城市微气候的基本概念各自进行了简单的介绍；并结合城市微气候中的概念对本文档中的UDF进行了简单介绍，目前本文档中的UDF主要针对城市风环境；最后推荐了一些城市微气候相关的书籍及论文文献。希望本文档中所讨论的内容能对各位同行今后的科研有所帮助。

## 2. Introduction of UDF UDF简介
There have been a bunch of documents talking about UDFs online. This document only focuses on UDFs related to urban microclimate. The background knowledge regarding UDF syntax and C programming is not discussed in this document. You can find numerous information online (for example [the ANSYS Fluent Help file for UDFs](https://www.afs.enea.it/project/neptunius/docs/fluent/html/udf/node4.htm#:~:text=A%20user%2Ddefined%20function%2C%20or,standard%20features%20of%20the%20code.)). UDFs are written in C. Therefore, users need to have some background in C programming or at least programming, no matter what language it is. The C codes of UDFs need to satisfy both C syntax and UDF "rules" (using predefined functions and macros in Fluent, check the Help file for more). UDFs in Fluent can be used to define specific properties for different variables, including boundary profiles (e.g. with varying velocity, temperature, concentration , etc.), material properties, chemical reaction constant, species source/sink term, and user defined scalars (UDSs), etc. 

本文档重点讨论的是有关城市微气候的内容，涉及UDF语法、C语言编程等内容不在本文的重点讨论范围内，相关资料可以在网上搜索到很多，这里只对UDF进行简单的介绍，以下内容引用自[流沙CAE的博客](http://blog.sina.com.cn/s/blog_599d8faa0102v3j7.html)：
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

通过上文的介绍，大家应该对UDF已经有了一个大概的印象，知道了UDF是什么、有什么用等等，这有助于大家进一步理解并学习UDF，更多的有关UDF具体编写及语法等内容，大家可以查阅Fluent的[Help文档](https://www.afs.enea.it/project/neptunius/docs/fluent/html/udf/node4.htm#:~:text=A%20user%2Ddefined%20function%2C%20or,standard%20features%20of%20the%20code.)。

## 3. Introduction of Urban Microclimate 城市微气候简介
Microclimate presents the local climate under a specific circumstance, which may have some different features from the surrounding environments. In a city scale, the local atmospheric environment usually exhibits quite different conditions at various locations, depending on local terrain, vegetation and greening, river and water, urban surface material, urban layout, building geometry and etc. It is usually called urban microclimate or urban microenvironment. Urban microclimate is associated with people's health, wellness, and comfort in the outdoor space, and will affect indoor environments as well. Urban microclimate usually includes multiple research areas, such as urban heat island (UHI), urban pollutant transmission, urban ventilation, and urban/building greening. It involves subjects like architecture, atmospheric environment, environmental science, urban design and urban planning. 

微气候是指在特定环境下不同于周围环境的当地小气候。而在城市尺度内，大气环境由于受到地形、植被绿化、水体、城市下垫面特征、城市布局形式、建筑物特征等因素的影响，常常表现出不同于周围大气环境的气候特点，这种现象也常被称为城市微气候。城市微气候常与城市环境中行人的健康、舒适性等直接相关，并间接影响室内环境。常见的如城市热岛现象（UHI, i.e. Urban Heat Island）、城市大气污染、建筑屋顶绿化、通风廊道等概念都属于城市微气候的研究范畴，涉及建筑、大气、环境、城市设计、城市规划等相关学科与领域。

Urban microclimate mainly include **Urban Thermal Environment, Urban Moist Environment, Urban Wind Environment (Urban Ventilation), Urban Pollutant and Atmospheric Environment, Urban Lighting Environment, and Urban Sound Environment**, etc. This document only focuses on **Urban Wind Environment (Urban Ventilation)** and **Urban Pollutant and Atmospheric Environment** as those were my major research areas. I'm actually unable to add more UDFs of other urban environment fields like thermal environment. If you are a researcher in urban microclimate field and you are willing to share your own UDFs of your research, please feel free to add more to this repo. Thanks. 

城市微气候主要包括：**城市热环境、城市湿环境、城市风环境、城市污染与大气环境、城市光环境、城市声环境**等。由于笔者的研究方向及个人水平的限制，目前本文档所涉及到的城市微气候内容只局限在对**城市风环境**与**城市污染与大气环境**的讨论。对于**城市热环境**、**城市湿环境**等其他方向，笔者目前及在可预见的未来都无法对其进行更多的研究并编写相关的UDF，希望能有同行对此进行研究并扩展相应的UDF，使之能应用到更为广泛的研究中。因此，本repo将仅针对于**城市风环境**与**城市污染与大气环境**进行讨论。

The following image is adapted from [a paper](http://www.sciencedirect.com/science/article/pii/S0360132315000724) of Prof. Bert Blocken (at TU/e). It describes the contents in urban physics and environments. 

下图摘自荷兰埃因霍温理工大学（TU/e）Bert Blocken教授的[一篇文章](http://www.sciencedirect.com/science/article/pii/S0360132315000724)，描述了城市物理环境所涉及到的内容。
![urbanphysics](https://github.com/kidisgod/UDF-of-Urban-Microclimate/blob/master/urbanphysics.png)

## 4. UDFs in Urban Microclimate 城市微气候相关UDF
### 4.1 Urban Wind Environment 城市风环境

Urban Wind Environment is essential for the general environment in the city. It may impact urban pollutant dispersion, urban ventilation, thermal bouyancy, and wind load on buildings. It also has great impacts on indoor environments such as indoor natural ventilation, building filtration, and indoor pollutant distribution as the ambient environment is the boundary of indoor spaces. Urban parameters like urban density, building height variation, and urban/street morphology will always affect the urban wind environment at a certain level. Besides, the inlet flow of the urban area, the vegetation/greening configurations of the city also impact the urban wind environment or urban ventilation.

城市风环境对于整个城市环境有巨大影响，涉及城市空气污染、自然通风、对流热交换、风荷载及城市风害等内容，同时城市风环境作为室内环境的边界条件也对室内环境有着重要影响。不同的城市密度、城市建筑高度变化、城市及街道形态等的变化都会影响一定尺度下的城市风环境。除了这一系列的城市、街道、建筑的形态会对城市风环境产生重要影响之外，城市区域的入口边界条件（inlet flow）、植被等也会影响城市内部的风环境。

- **Inlet Profile 入口边界条件**

|Relevant UDFs 相关UDF|
|---|
|[**udf_of_inlet.c**](https://github.com/jialeishen/UDF-of-Urban-Microclimate/blob/master/udf_of_inlet.c)|

It sets up the inlet flow profiles, including inlet velocity and turbulence. The velocity profile in the file uses an exponential distribution as the example, which can be revised accordingly. 入流边界条件，包括速度项、湍动能项、湍流耗散率项。这里速度项以指数分布为例，可以根据具体要求进行修改。

![inletflow](https://github.com/kidisgod/UDF-of-Urban-Microclimate/blob/master/inletflow.png)

- **Vegetation/Greening on Airflow Field 植被对风场的影响**

|Relevant UDFs 相关UDF|
|---|
|[**udf_of_tree.c**](https://github.com/jialeishen/UDF-of-Urban-Microclimate/blob/master/udf_of_tree.c)|

It considers the impacts of vegetation and greening on airflow field, including some source terms of velocity and turbulence. 植被对流场的影响，包括速度源项、湍动能源项、湍流耗散率源项。

- **Urban Ventilation Evaluation Indices 通风评价指标**

|Relevant UDFs 相关UDF|
|---|
|[**udf_of_source_particular_area.c**](https://github.com/jialeishen/UDF-of-Urban-Microclimate/blob/master/udf_of_source_particular_area.c)|
|[**udf_of_urban_ventilation_indices.c**](https://github.com/jialeishen/UDF-of-Urban-Microclimate/blob/master/udf_of_urban_ventilation_indices.c)|

It sets up a pollutant source term in a specific location. 污染物源项，在特定区域内设定污染物源项。

It includes some commonly used indices for evaluating the urban ventilation performance, e.g. Purging flow rate, Local mean age of air, Mean residence time, Visitation frequency, Average residence time, Flow rate, Turn-over time, Air change rate, Air exchange efficiency. For more information, I'd like to recommend a great review paper introduced these indices - [Indices employed for the assessment of “urban outdoor ventilation” - A review](http://dx.doi.org/10.1016/j.atmosenv.2019.117211). 城市通风评价指标，包括Purging flow rate，Local mean age of air，Mean residence time，Visitation frequency，Average residence time，Flow rate，Turn-over time，Air change rate，Air exchange efficiency。一篇优秀的介绍各类通风指标的文献综述：[Indices employed for the assessment of “urban outdoor ventilation” - A review](http://dx.doi.org/10.1016/j.atmosenv.2019.117211)。

### 4.2 Urban Pollutant and Atmospheric Environment 城市污染与大气环境

It includes some pollutant-related files, including reactive and passive pollutants. They might also be introduced in some other repos of mine. 

一些大气污染物相关的UDF或相关计算。在笔者其他repo中有涉及到一些（原用于室内环境，亦可推广至城市环境），例如：

- [**Ozone deposition and chemical reaction 臭氧反应与沉降**](https://github.com/jialeishen/UDF-of-Indoor-Ozone-Deposition)

|Relevant UDFs 相关UDF|
|---|
|[**udf_ozone_deposition.c**](https://github.com/jialeishen/UDF-of-Indoor-Ozone-Deposition/blob/master/udf_ozone_deposition.c)|
|[**udf_ozone_deposition_and_chemical_reaction.c**](https://github.com/jialeishen/UDF-of-Indoor-Ozone-Deposition/blob/master/udf_ozone_deposition_and_chemical_reaction.c)|

It includes the ozone deposition on different surfaces, and the generation of by-products, including some ozone-related source/sink terms. 臭氧在材料表面的沉降及化学反应生成副产物（by-products）的过程，包含臭氧与化合物的源项/汇项。

- [**VOC reaction and removal VOCs反应与沉降**](https://github.com/jialeishen/UDF-Formaldehyde-Adsorption)*(Formaldehyde as the example 以甲醛为例)*

|Relevant UDFs 相关UDF|
|---|
|[**UDF_Formaldehyde_Adsorption.c**](https://github.com/jialeishen/UDF-Formaldehyde-Adsorption/blob/master/UDF_Formaldehyde_Adsorption.c)|

The process of formaldehyde reactions with other VOCs, and the generation of secondary emissions. It includes some source/sink terms of VOCs. 甲醛与其他化合物反应生成其他副产物的过程，包含甲醛与化合物的源项/汇项。

- [**Particle natural deposition 颗粒物沉降**](https://github.com/jialeishen/ParticleDeposition)*(theoretical modeling, not a UDF 理论计算，非UDF)*

|Relevant modeling 相关计算|
|---|
|[**particledeposition.m**](https://github.com/jialeishen/ParticleDeposition/blob/master/particledeposition.m)|
|[**vd_empirical.m**](https://github.com/jialeishen/ParticleDeposition/blob/master/vd_empirical.m)|

It models the particle natural deposition on different surfaces using Matlab (not a UDF file). But the theoretical model can be adapted in UDFs. 颗粒物在表面的沉降的理论计算（非UDF），但该理论公式可被用于UDF中来计算颗粒物的沉降。

## 5. Tutorials of Application of UDFs in Fluent 相关UDF解释与教程

Now you have a brief overview on different UDFs of urban microclimate. But how can you really use them in Fluent and what does each command/code of the UDF file mean? You can always find the Help file in Fluent and it can likely solve almost 100% of all questions you have. I have also drafted a few tutorials documents about that, which are listed below. Feel free to find and read them if you needed. It might provide you some helps on understanding UDF files and the applications of them. All these documents were written in Chinese. For English-speaking readers, you can actually find many similar tutorials or documents on Google or Youtube. Please do so if you need. 

UDF相关的代码与各类宏的介绍，可以参见ANSYS Fluent官方的UDF教程，你可以在你的Fluent的Help中找到相关文档。网络上亦有一些相关的教程，请自行搜索。本repo中涉及到的一些UDF代码均带有一些注释，可以配合注释来理解这些UDF代码。此外，也以部分UDF文件为例，写了比较详尽的解释文档，如下所示。这应该会对你的理解有所帮助。这些文档写于多年前，如有任何错误请大家指出。

 - [Tutorial 1 - ICEM划分结构网格](https://github.com/jialeishen/UDF-of-Urban-Microclimate/blob/master/Tutorial%201%20-%20ICEM%E5%88%92%E5%88%86%E7%BB%93%E6%9E%84%E7%BD%91%E6%A0%BC.pdf)

 - [Tutorial 2 - udf_example](https://github.com/jialeishen/UDF-of-Urban-Microclimate/blob/master/Tutorial%202%20-%20udf_example.pdf)

 - [Tutorial 3 - udf说明](https://github.com/jialeishen/UDF-of-Urban-Microclimate/blob/master/Tutorial%203%20-%20udf%E8%AF%B4%E6%98%8E.pdf)

 - [Tutorial 4 - udf载入操作](https://github.com/jialeishen/UDF-of-Urban-Microclimate/blob/master/Tutorial%204%20-%20udf%E8%BD%BD%E5%85%A5%E6%93%8D%E4%BD%9C.pdf)


## 6. More Information 更多阅读

This document only exhibits very limited information in urban microclimate. If you're interested in reading more relevant contents, there are a few books and papers I highly recommended, particularly for the beginners. 

限于篇幅，本文档对于城市微气候的介绍十分有限，如果有兴趣继续了解更多城市微气候相关的内容，以下是一些笔者个人推荐的书籍与综述性论文，供各位参考学习：
  
### 6.1 Books 参考书：

Some books I read during my first studies in this area. Most of them are in Chinese language.

 (1) [Urban Environment Physics 城市环境物理](https://www.amazon.cn/%E5%9F%8E%E5%B8%82%E7%8E%AF%E5%A2%83%E7%89%A9%E7%90%86-%E5%88%98%E5%8A%A0%E5%B9%B3/dp/B004X8RC6A/ref=sr_1_1?ie=UTF8&qid=1478336099&sr=8-1&keywords=%E5%9F%8E%E5%B8%82%E7%8E%AF%E5%A2%83%E7%89%A9%E7%90%86)(A Chinese book)

Highly recommanded for Chinese-speaking readers. Much of the content in this document was inspired by this book. 强烈推荐，本文档有大量内容直接摘自《城市环境物理》的各个章节或受其启发。

 (2) [CFD与建筑环境设计](https://www.amazon.cn/CFD%E4%B8%8E%E5%BB%BA%E7%AD%91%E7%8E%AF%E5%A2%83%E8%AE%BE%E8%AE%A1-%E6%9D%91%E4%B8%8A%E5%91%A8%E4%B8%89/dp/B0012782NW/ref=sr_1_1?ie=UTF8&qid=1478336169&sr=8-1&keywords=CFD%E4%B8%8E%E5%BB%BA%E7%AD%91%E7%8E%AF%E5%A2%83%E8%AE%BE%E8%AE%A1)(A Japanese book, but was translated into Chinese. No English version available probably)

This book includes CFD simulations for both indoor and outdoor environments. You can just focus on the outdoor part if you are only interested in that. 此书的大部分内容介绍的是室内环境，大家可以只看其室外环境部分

 (3) [Urban Microclimate: Designing the Spaces Between Buildings](https://www.amazon.cn/Urban-Microclimate-Designing-the-Spaces-Between-Buildings-Erell-Evyatar/dp/B008FYSNL6/ref=sr_1_1?ie=UTF8&qid=1478336175&sr=8-1&keywords=Urban+Microclimate%3A+Designing+the+Spaces+Between+Buildings)(An English book, but was translated into Chinese)

This is a very good book for English-speaking readers, particularly the beginners in this field. 本书有[中文翻译版](https://www.amazon.cn/%E5%9F%8E%E5%B8%82%E5%B0%8F%E6%B0%94%E5%80%99-%E5%BB%BA%E7%AD%91%E4%B9%8B%E9%97%B4%E7%9A%84%E7%A9%BA%E9%97%B4%E8%AE%BE%E8%AE%A1-%E5%9F%83%E7%BB%B4%E7%89%B9%C2%B7%E5%9F%83%E9%9B%B7%E5%B0%94/dp/B00JL2FMZQ/ref=sr_1_3?ie=UTF8&qid=1478336175&sr=8-3&keywords=Urban+Microclimate%3A+Designing+the+Spaces+Between+Buildings)，但是翻译质量略差，建议大家配合英文原版阅读。

### 6.2 Review Papers 综述性论文：

 (1) [Study on Interrelationship between Urban Pattern and Urban Microclimate 城市形态与城市微气候的关联性研究](http://www.cnki.net/KCMS/detail/detail.aspx?QueryID=3&CurRec=1&recid=&filename=JZXB201207005&dbname=CJFD2012&dbcode=CJFQ&pr=&urlid=&yx=&uid=WEEvREcwSlJHSldRa1FhcEE0L01SOC9Bb2NIa3FuWWNUc3RjVndKTjBhaz0=$9A4hF_YAuvQ5obgVAqNKPCYcEjKensW4ggI8Fm4gTkoUKaID8j8gFw!!&v=MzE3NDc0SDlQTXFJOUZZWVI4ZVgxTHV4WVM3RGgxVDNxVHJXTTFGckNVUkx5ZVp1WnFGeTdrVWJ2TUx6ZlRiTEc=) (a classical review paper in Chinese language written by my former colleagues)

 (2) [AIJ guidelines for practical applications of CFD to pedestrian wind environment around buildings](http://www.sciencedirect.com/science/article/pii/S0167610508000445)

 (3) [Indices employed for the assessment of “urban outdoor ventilation” - A review](http://dx.doi.org/10.1016/j.atmosenv.2019.117211)

 (4) [Modelling air qualityin street canyons: a review](http://www.sciencedirect.com/science/article/pii/S1352231002008579)

 (5) [Application of computational fluid dynamics in building performance simulation for the outdoor environment: an overview](http://china.tandfonline.com/doi/abs/10.1080/19401493.2010.513740)

 *Only a few review papers are listed above. You can find more research articles [online](https://scholar.google.com/).*

 *注：这里只推荐了几篇综述性论文，还有大量相关研究论文，请各位自行[查阅](https://scholar.google.com/)*
 
 ### 6.3 My Research Papers 笔者相关论文：
 
I have also published a few papers in the urban microclimate area, which includes studies in **urban wind environment**, **urban ventilation and pollutant dispersion**, **impacts of urban greening on urban thermal environment and pollutant dispersion**, **human exposure to air pollutants in transportation environments**, etc. Some of those papers are listed below. Thanks in advance for your reading and citation if you are interested in them. You can find and download all full papers for free on my [personal website](http://www.jialeishen.com/publications/) in case you are not able to access some of them.
 
最后是一些笔者参与发表的城市微气候相关的论文，涉及**城市风环境**，**街道通风与污染物扩散**，**植被与绿化对城市热环境与污染物扩散的影响**，**交通环境的人体污染物暴露**等。欢迎各位同行阅读与引用，谢谢！若您无法获取这些论文，也可在[笔者主页上](http://www.jialeishen.com/publications/)找到全文并下载。

 (1) [An investigation on the effect of street morphology to ambient air quality using six real-world cases](https://doi.org/10.1016/j.atmosenv.2017.05.047)

 (2) [The Impact of Green Space Layouts on Microclimate and Air Quality in Residential Districts of Nanjing, China](https://doi.org/10.3390/f9040224)
 
 (3) [Improving residential building arrangement design by assessing outdoor ventilation efficiency in different regional spaces](https://doi.org/10.1080/00038628.2018.1471388)

 (4) [Commuter exposure to particulate matters in four common transportation modes in Nanjing](https://doi.org/10.1016/j.buildenv.2019.04.018)
 
 (5) [Urban ventilation of typical residential streets and impact of building form variation](https://doi.org/10.1016/j.scs.2021.102735)
 
 (6) [On the effects of urban-like intersections on ventilation and pollutant dispersion](https://link.springer.com/article/10.1007/s12273-021-0816-5)
 
 (7) [Effect of greening on pollutant dispersion and ventilation at urban street intersections](https://doi.org/10.1016/j.buildenv.2021.108075)
 
 (8) [Improving Wind Environment of Residential Neighborhoods by Understanding the Relationship between Building Layouts and Ventilation Efficiency](https://doi.org/10.1016/j.egypro.2017.03.972)
 
 (9) [Improving wind environment design based on assessing spatial distribution of ventilation efficiency in regional space](https://doi.org/10.1016/j.egypro.2017.12.418)
 
Feel free to let me know if you have any questions or comments on this document or my researches. Corrections or suggestions on the contents in this document are always welcome. I'm open to have any discussions with you. You can always find me through my personal website: www.jialeishen.com

本文档介绍了几个常用的城市微气候的UDF，同时简单介绍了城市微气候相关内容，希望这些UDF和介绍内容可以对各位同行日后的科研有所帮助或启发，同时**强烈邀请**大家对本文档内容进行修改及补充！！也欢迎同行分享更多城市微气候相关的UDF，欢迎共同交流。作者：www.jialeishen.com 

Updated 更新：2022/04/30
