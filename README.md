## 概要
DXライブラリを使用したノベルゲームのサンプルです。  
ただ現状最低限すら実装できていません  

## 使い方
Dxライブラリが必要です。  
下記Visual Studioの設定をしてビルドをする必要があります。  

## 開発環境構築（ビルド設定）について  
Visual Studio Community 2017以降 推奨 (C++14の機能一部使用)  

### Dxライブラリのインストール
https://dxlib.xsrv.jp/dxdload.html  
よりVisual Studio用のをダウンロードして、
DxLib_VC3_21.zipを展開します。  
解凍後DxLib_VCというフォルダがあるので、それを  
`C:\Library\`ディレクトリを作成し、`C:\Library\`に移動させます。  
  
`C:\Library\DxLib_VC\プロジェクトに追加すべきファイル_VC用`を  
`C:\Library\DxLib_VC\DxLibrary`に名前変更します。  
以上でDxライブラリのインストールは終わりです。  

### Visual Studioの設定について
なお、DXライブラリのパスは  
`C:\Library\DxLib_VC\DxLibrary`  
としています。  
さらにシステム環境変数に  
`DX_LIB_VC_DIR`  
に上記パス(`C:\Library\DxLib_VC\DxLibrary`)を登録しています。  
このあたりはVisual Studioのプロジェクトの`プロパティ ページ`の  
`追加のインクルードディレクトリ`等を見ていただければわかります。  

## ライセンス
あとで準備  
基本的にMITとかにすると思います。  

## 参考実装など
https://dxlib.xsrv.jp/dxprogram.html#N19
