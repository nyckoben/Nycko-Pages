# 本人主页
[https://nyckoben.github.io/Nycko-Pages/](https://nyckoben.github.io/Nycko-Pages/)
# 基于
[主题GitHub](https://github.com/kaeyleo/jekyll-theme-H2O),
[作者主页](http://liaokeyu.com),
[主题介绍](http://liaokeyu.com/%E6%8A%80%E6%9C%AF/2017/04/18/new-theme-h2o.html)  
大部分基础使用方法，参照原作者的README吧
  
# 部署参考
谈不上教程，简单讲几句搭建过程上遇到的问题。
* 建议不要安装Ruby最新版，我使用的是2.3.3_x64
* 并没有升级gem
* ruby安装完直接在官网下载DevKit，这时你就知道为什么不要安装最新的Ruby了，最新版本是自动通过网络获取的，自备梯子吧
* 网上各种主题在jekyll serve时都会报错，大概因为你没有bundle install，这个过程梯子也很重要，否则就找个没有bundle需求的主题吧，比如这个
* 当你发现本都jekyll serve可以正常显示，但是部署好了却各种缺失时，F12看看控制台输出什么，一般都是路径设置问题，跟着代码一点点修改自己的路径吧，我也这么过来的

# Bug
本人不熟前端，都是跟着chrome调试提示的错误找到代码一点点修改的
*  由于模板不少地方使用的url只有http://username.github.io/，而并没有仓库名，  
但其实_config.yml有定义该变量，所以在必要的地方加上了
```
| prepend: site.baseurl 
或者
{{ site.baseurl }}
```

### 已发现而未处理的问题  
	本小白从0开始安装jekyll，到现在基本可以正常写作，一共3天，生怕自己陷于ui和功能，而忘却了内容，于是记录以下已发现问题，日后逐步解决以及增加功能。
* cover图片的路径还没有完美解决，原作者使用网络图片，而我想使用仓库内的图片，现在直接在文章中不使用cover，以后再处理
* 该模板带的Disqus，由于没有翻墙，所以直接屏蔽
* 夜间模式字体灰色，对比度较小，自我感觉不好，屏蔽。日后调整字体颜色后再开启
* 搜索模块，随手测试了一下，用不起来，原因未知，屏蔽，日后文章多了再处理
* categories分类，不管按日期还是按什么分类，日后文章多了肯定要处理，暂时屏蔽
* 从其他页面跳转到tags.html是，原作是用#跳转该页面指定位置的，但是我部署出来有bug，暂时仅跳转到tags.html了事
* 很想要统计功能，貌似本来就有，以后一定要弄好