---
layout: post
title: '使用sourcetree管理GitHub/Gitee/bitbucket等git平台'
subtitle: '分享一下Pull Request成功的小喜悦'
date: 2018-05-10
categories: C++
tags: Common C++
---

# 本人第一次Pull Request经历
很多人知道Git，开始使用了，也许也没有体会到Git平台的意义，这里分享一下，一定程度上了解一下  
* 首先是本人需要使用OpenSsl从事PKI相关工作，由于需要开发国密SM2/SM3/SM4/SM9等，所以转而使用[GmSSL](http://gmssl.org/)
* 参考源码测试示例代码，在开发SM2加解密功能时，遇到解密失败，从调用代码检查清楚无发现错误后，怀疑是否某些参数设置错误，转而研究其源码，最后发现返回值在返回前被释放，经过测试，确定这就是罪魁祸首：
```cpp
    SM2CiphertextValue *ret = NULL;
    SM2CiphertextValue *cv = NULL;
    /*.......*/
    ret = cv;
end:
    SM2CiphertextValue_free(cv);
    return ret;
```
* 解决办法只需要在ret = cv;后加上cv = NULL;紧接着的free语句是支持NULL而不做任何工作的
* 那么问题来了，虽然发现了bug，也能解决，但是如果你只修改本地代码，那么官方更新了什么功能，下载新源码后又需要修改该bug，麻烦。
## pull request
* 