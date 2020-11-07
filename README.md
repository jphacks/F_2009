# 安心ふろ～（風呂xTech）

[![ロゴ](frontend/assets/logo/anshin_furow.png)](https://youtu.be/iCerLnWxvVQ)


## 製品概要
### 背景(製品開発のきっかけ、課題等）
[内閣府の発表](https://www8.cao.go.jp/kourei/whitepaper/w-2017/html/zenbun/s1_2_1.html)によると，2017年の時点で65歳以上の高齢者のいる世帯の約26%が単独世帯となっており，年々増加傾向にあります．**単独世帯において，高齢者が一人で住んでいる場合，高齢者に何か異常があっても誰も検知することができません．** また，身内（子供や孫）が離れた場所に住んでいて検知が遅れる場合があります．

特に風呂場では寒暖の急激な差が発生し，ヒートショック等で年間約1万9000人も風呂場で亡くなっています．また，そのうち9割以上は65歳以上の高齢者という事実もあります．

そこで，今回は単独世帯の高齢者をターゲットとして，**風呂場での高齢者の異常を検知**，そして**遠く離れた身内に通知**してくれるサービスを考案しました．


### 製品説明（具体的な製品の説明）

IoTデバイスとスマホアプリを用いて，風呂場での高齢者の異常を検知してアラートしてくれるサービスです．

IoTデバイスを用いて，風呂場に「入った」or「出た」を検知します．
RFIDの認証と距離センサで風呂場の扉の開閉検知から，入浴時間を計測します．

入浴時間のデータは常に蓄積しており，過去のデータからその人の平均入浴時間を算出し，異常な入浴時間の時にユーザーのスマホに通知がきます．

![IoT Device](https://user-images.githubusercontent.com/49345024/98411801-10a22600-20ba-11eb-8396-64ec01ce0d45.jpg)

<p float="left">
  <img src="https://github.com/jphacks/F_2009/blob/frontend_Nokubi/Frontend/static/bath5.png" width="200" />
  <img src="https://github.com/jphacks/F_2009/blob/frontend_Nokubi/Frontend/static/bath4.png" width="200" /> 
  <img src="https://github.com/jphacks/F_2009/blob/frontend_Nokubi/Frontend/static/bath3.png" width="200" />
  <img src="https://github.com/jphacks/F_2009/blob/frontend_Nokubi/Frontend/static/bath1.png" width="200" />
</p>


### 特長
#### 特徴1 手軽に導入できる！

#### 特徴2 遠く離れていても入浴の安否が通知される！

#### 特徴3 過去の入浴データから生活リズムが確認できる！(生存確認にも)


### 解決出来ること

高齢者の異常が発生した時に，だれも気付かずに手遅れになってしまうことを防ぎます！


### 使い方

* アプリ側<br/>
<p display="flex">
  <div>1. QRコードからデバイスを登録</div>  <br/>
  <div><img src="https://github.com/jphacks/F_2009/blob/frontend_Nokubi/Frontend/static/qrread.jpg" width="350" /></div> 
</P><br/>
<p float="left">
  <div>2. IoTデバイスが作るアクセスポイントに接続し，IoTデバイスのネットワークを設定（Alex◯方式）  </div><br/>  
  <img src="https://github.com/jphacks/F_2009/blob/frontend_Nokubi/Frontend/static/wificonnectview.jpg" width="350" /> 
</p><br/>
<p float="left">
  <div>3. アプリから現在の入浴状況を確認できます  </div>  <br/>
  <p float="left">
    <img src="https://github.com/jphacks/F_2009/blob/frontend_Nokubi/Frontend/static/bath4.png" width="350" /> 
    <img src="https://github.com/jphacks/F_2009/blob/frontend_Nokubi/Frontend/static/bath3.png" width="350" />
  </p>
</p><br/>
<p float="left">
  <div>4. 異常事態発生時には，通知が来ます  </div>  <br/>
  <img src="https://github.com/jphacks/F_2009/blob/frontend_Nokubi/Frontend/static/announce.png" width="350" />  
</p><br/>

* デバイス側  <br/>
<p float="left">
  <div>1, 入浴時にRFIDtタグをかざしてもらうだけです！</div><br/>  
  <img src="https://github.com/jphacks/F_2009/blob/frontend_Nokubi/Frontend/static/touch.png" width="350" />
</p><br/>
<p float="left">
  <div>2. 異常時はIoTデバイスからもブザーが鳴り，本人にも通知され誤検知を防ぎます.</div><br/>  
  <img src="https://github.com/jphacks/F_2009/blob/frontend_Nokubi/Frontend/static/deviceview.jpg" width="350" />  
</p>

### 今後の展望
* 気圧センサや人感センサ等を駆使して，異常検知の精度を上げる．
* 回路基盤を設計・発注（発注に2週間程度かかかる）して，もっとデバイスをコンパクトにしてより使ってもらいやすくする．
* 近くの介護施設や，地方自治体の福祉課とも提携して，すばやく高齢者の状態を確認できるように通報機能を強化する．
* 集めた入浴データを用いてどの時間帯に風呂場に入るのか，どのぐらいの時間はいるのかを推測や異常検知の精度向上に利用できる．


### 注力したこと（こだわり等）
* **とにかく手軽に誰でも簡単に導入できる**  
  デバイス単価も安く，またアプリから登録して簡単に使用できる．(使い方もアプリページに記載) \
  また，アプリのデザインも入浴状態が一目で誰でも確認できるようになっている．\
  通知機能も，ネイティブの通知機能を使用しているためスリープモードでも通知される．  
* **個人ごとの過去の入浴データをため続けられる**  
  個人ごとの過去の入浴データをもとに，何分以上入り続けていたら異常とするかを個人ごとに算出． \
  また，データがたまると機械学習によって，より精度を上げることができる．
 
## 開発技術
### 活用した技術
#### API・データ
* DB管理・データ通信用独自API（PHP, Flask）

#### フレームワーク・ライブラリ・モジュール
* Nuxt（フロント開発）
* Flask（API開発）

#### デバイス
* ESP32（Wi-Fi/BLE対応省電力IoTデバイス）
* 距離センサ
* RFID

### 独自技術
#### ハッカソンで開発した独自機能・技術
* **「安心ふろ〜」は新規開発**
* WEBアプリと風呂の利用状況を監視・記録するIoTデバイスを独自開発！
* hardwareフォルダにIoTデバイスのファイルや詳細情報・設計情報は記載
* 過去の入浴記録を基に緊急状態の条件を算出, 記録が更新されるたびに改善！

## デモ動画
デモ動画<a href="https://www.youtube.com/watch?v=iCerLnWxvVQ&feature=youtu.be">こちら</a>から. \
README上部のロゴをクリックしても動画ページに遷移できます!
