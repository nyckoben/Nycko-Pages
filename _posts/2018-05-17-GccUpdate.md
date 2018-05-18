---
layout: post
title: '升级Gcc'
subtitle: 'yum升级Gcc'
date: 2018-05-17
categories: C++
tags: Common C++
---

虽然网上一捉一大把，但是遇到了点问题，这里自己记录以下
```
mv /etc/yum.repos.d /etc/yum.repos.d.bak
wget http://people.centos.org/tru/devtools-2/devtools-2.repo
mv devtools-2.repo /etc/yum.repos.d
yum install devtoolset-2-gcc devtoolset-2-binutils devtoolset-2-gcc-c++
```
最后一步yum install可能会遇到repo文件有问题，跟环境变量应该有关系
devtools-2.repo：
```

```