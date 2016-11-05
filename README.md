# UDF of Urban Microclimate
##城市微气候简介
本文档包含了一些在使用商用CFD软件ANSYS Fluent®模拟城市微气候（Urban Microclimate）时，常用到的用户自定义函数（UDF, i.e. User Defined Function）。微气候是指在特定环境下不同于周围环境的当地小气候。而在城市尺度内，大气环境由于受到地形、植被绿化、水体、城市下垫面特征、城市布局形式、建筑物特征等因素的影响，常常表现出不同于周围大气环境的气候特点，这种现象也常被称为城市微气候。城市微气候常与城市环境中行人的健康、舒适性等直接相关，并间接影响室内环境。常见的如城市热岛现象（UHI, i.e. Urban Heat Island）、城市大气污染、建筑屋顶绿化、通风廊道等概念都属于城市微气候的研究范畴，涉及建筑、大气、环境、城市设计、城市规划等相关学科与领域。

##UDF简介

在使用商用CFD软件ANSYS Fluent®研究城市微气候时，常常需要根据城市微气候的各特点编写用户自定义函数UDF来模拟真实的城市环境，这里列举了一些常用的UDF：

- **udf_of_inlet.c**

入流边界条件，包括速度项、湍动能项、湍流耗散率项。这里速度项以指数分布为例，可以根据具体要求进行修改。

- **udf_of_source_particular_area.c**

污染物源项，在特定区域内设定污染物源项。

- **udf_of_tree.c**

植被对流场的影响，包括速度源项、湍动能源项、湍流耗散率源项。

- **udf_of_urban_ventilation_indices.c**

城市通风评价指标，包括Purging flow rate，Local mean age of air，Mean residence time，Visitation frequency，Average residence time，Flow rate，Turn-over time，Air change rate，Air exchange efficiency

---

可以看到，这里的UDF主要都是针对城市风环境，而对于城市热环境、水体对城市环境的影响等因素都没有被包括进去，由于研究方向及个人能力的限制，目前作者无法对其进行更多的研究并编写相关的UDF，希望能有更多同学对此进行研究并扩展UDF，使之能应用到更多研究情况中。

##相关文献推荐

限于篇幅，本文档对于城市微气候的介绍十分有限，如果有兴趣继续了解更多城市微气候相关的内容，以下是一些个人推荐的书籍与综述性论文，供大家参考学习：
  
###参考书：

1.[Urban Microclimate: Designing the Spaces Between Buildings](https://www.amazon.cn/Urban-Microclimate-Designing-the-Spaces-Between-Buildings-Erell-Evyatar/dp/B008FYSNL6/ref=sr_1_1?ie=UTF8&qid=1478336175&sr=8-1&keywords=Urban+Microclimate%3A+Designing+the+Spaces+Between+Buildings)

本书有[中文翻译版](https://www.amazon.cn/%E5%9F%8E%E5%B8%82%E5%B0%8F%E6%B0%94%E5%80%99-%E5%BB%BA%E7%AD%91%E4%B9%8B%E9%97%B4%E7%9A%84%E7%A9%BA%E9%97%B4%E8%AE%BE%E8%AE%A1-%E5%9F%83%E7%BB%B4%E7%89%B9%C2%B7%E5%9F%83%E9%9B%B7%E5%B0%94/dp/B00JL2FMZQ/ref=sr_1_3?ie=UTF8&qid=1478336175&sr=8-3&keywords=Urban+Microclimate%3A+Designing+the+Spaces+Between+Buildings)，但是翻译的质量太差，强烈不建议大家阅读中文翻译版

2.[城市环境物理](https://www.amazon.cn/%E5%9F%8E%E5%B8%82%E7%8E%AF%E5%A2%83%E7%89%A9%E7%90%86-%E5%88%98%E5%8A%A0%E5%B9%B3/dp/B004X8RC6A/ref=sr_1_1?ie=UTF8&qid=1478336099&sr=8-1&keywords=%E5%9F%8E%E5%B8%82%E7%8E%AF%E5%A2%83%E7%89%A9%E7%90%86)

强烈推荐

3.[CFD与建筑环境设计](https://www.amazon.cn/CFD%E4%B8%8E%E5%BB%BA%E7%AD%91%E7%8E%AF%E5%A2%83%E8%AE%BE%E8%AE%A1-%E6%9D%91%E4%B8%8A%E5%91%A8%E4%B8%89/dp/B0012782NW/ref=sr_1_1?ie=UTF8&qid=1478336169&sr=8-1&keywords=CFD%E4%B8%8E%E5%BB%BA%E7%AD%91%E7%8E%AF%E5%A2%83%E8%AE%BE%E8%AE%A1)

本书的大部分内容介绍的是室内环境，大家可以只看其室外环境部分

*注：第一本英文书[图书馆](http://lib.nju.edu.cn/html/index.html)没有馆藏，但丁老师工作室有其影印版。其中文翻译版及另外两本中文书籍图书馆均有馆藏*

###综述性论文：

1.[城市形态与城市微气候的关联性研究](http://www.cnki.net/KCMS/detail/detail.aspx?QueryID=3&CurRec=1&recid=&filename=JZXB201207005&dbname=CJFD2012&dbcode=CJFQ&pr=&urlid=&yx=&uid=WEEvREcwSlJHSldRa1FhcEE0L01SOC9Bb2NIa3FuWWNUc3RjVndKTjBhaz0=$9A4hF_YAuvQ5obgVAqNKPCYcEjKensW4ggI8Fm4gTkoUKaID8j8gFw!!&v=MzE3NDc0SDlQTXFJOUZZWVI4ZVgxTHV4WVM3RGgxVDNxVHJXTTFGckNVUkx5ZVp1WnFGeTdrVWJ2TUx6ZlRiTEc=)

2.[AIJ guidelines for practical applications of CFD to pedestrian wind environment around buildings](http://www.sciencedirect.com/science/article/pii/S0167610508000445)

3.[Thermal comfort: A review paper](http://www.sciencedirect.com/science/article/pii/S1364032110002200)

4.[Modelling air qualityin street canyons: a review](http://www.sciencedirect.com/science/article/pii/S1352231002008579)

5.[Urban Physics:Effect of the micro-climate on comfort,health and energy demand](http://www.sciencedirect.com/science/article/pii/S2095263512000301)

6.[Approaches to study Urban Heat Island-Abilities and limitations](http://www.sciencedirect.com/science/article/pii/S0360132310001083)

7.[A review on the generation, determination and mitigation of Urban Heat Island](http://www.sciencedirect.com/science/article/pii/S1001074208600194)

8.[Cooling the cities – A review of reflective and green roof mitigation technologies to fight heat island and improve comfort in urban environments](http://www.sciencedirect.com/science/article/pii/S0038092X12002447)

9.[Computational Fluid Dynamics for urban physics: Importance, scales, possibilities, limitations and ten tips and tricks towards accurate and reliable simulations](http://www.sciencedirect.com/science/article/pii/S0360132315000724)

10.[Application of computational fluid dynamics in building performance simulation for the outdoor environment: an overview](http://china.tandfonline.com/doi/abs/10.1080/19401493.2010.513740)

 *注：这里只推荐了几篇综述性论文，还有大量相关研究论文，请大家自行[查阅](http://www.sciencedirect.com/)*

----

本文档介绍了几个常用的城市微气候的UDF，同时简单介绍了城市微气候相关内容，希望这些UDF和介绍内容可以在大家日后的科研中对大家有所帮助，同时强烈邀请大家对本文档内容进行修改及补充！！也欢迎大家上传更多相关的UDF。作者联系邮箱：shenjialei1992@163.com
