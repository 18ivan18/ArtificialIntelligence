(this["webpackJsonptic-tac-toe"]=this["webpackJsonptic-tac-toe"]||[]).push([[0],[,,,,,,,,,,function(t,n,e){},function(t,n,e){},function(t,n,e){},function(t,n,e){"use strict";e.r(n);var r=e(0),i=e(1),o=e.n(i),c=e(4),a=e.n(c),s=e(2),u=function(t){var n=t.highlightWinSquares,e=t.value,i=t.updateStateOnClick;return Object(r.jsx)("div",{className:n,onClick:i,children:e})},l=(e(10),function(t){var n=t.board,e=t.updateBoard,i=t.reset,o=t.winningSquares,c=function(t,n){var e="square";return o.length>0&&o.forEach((function(r){r.x===t&&r.y===n&&(e="square winningSquare")})),e},a=function(t,n){return t.map((function(t,i){return Object(r.jsx)(u,{highlightWinSquares:c(n,i),value:t,updateStateOnClick:function(){return e(n,i)}},i)}))};return Object(r.jsx)("div",{children:Object(r.jsxs)("div",{className:"board",children:[function(t){return t.squares.map((function(t,n){return Object(r.jsxs)("div",{className:"row",children:[" ",a(t,n)]},n)}))}(n),Object(r.jsx)("div",{className:"btnCountainer",children:Object(r.jsx)("button",{className:"btn",onClick:i,children:"Reset"})})]})})}),f=(e(11),function(t){var n=t.state,e=t.reset,i=t.jumpTo,o=n.history.map((function(t,n){var e=n?"Go to move #"+n:"Go to game start",o="";return o=t.active?"active":"normal",Object(r.jsx)("li",{children:Object(r.jsx)("button",{className:o,onClick:function(){return i(n)},children:"".concat(e," (").concat(t.location.row,", ").concat(t.location.col,")")},"".concat(t.location.col,"_").concat(t.location.row))},n)}));return Object(r.jsxs)("div",{className:"statistics",children:[n.result&&Object(r.jsxs)("div",{className:"stats",children:["win"===n.result.status?"WIN":"Draw",Object(r.jsx)("br",{}),Object(r.jsx)("button",{onClick:e,className:"stats",children:"Play again"})]}),n.result&&"win"===n.result.status&&Object(r.jsxs)("div",{className:"stats",children:["Winner: ",n.result.win.player]}),!n.result&&Object(r.jsxs)("div",{className:"stats",children:["Turn player: ",n.xIsNext?"X":"O"]}),Object(r.jsx)("ol",{children:o})]})}),h=null,x=Math.max,d=Math.min,v=function t(n,e,r,i,o){var c=g(n);if(0===e||c)return b(c,e);if(o){var a=-1/0;return n.forEach((function(o,c){return o.forEach((function(o,s){if(o===h&&(n[c][s]="X",a=x(a,t(n,e-1,r,i,!1)),r=x(r,a),n[c][s]=h,i<=r))return a}))})),a}var s=1/0;return n.forEach((function(o,c){return o.forEach((function(o,a){if(o===h&&(n[c][a]="O",s=d(s,t(n,e-1,r,i,!0)),i=d(i,s),n[c][a]=h,i<=r))return s}))})),s},y=function(t,n){var e=n?-1/0:1/0,r={};return t.forEach((function(i,o){return i.forEach((function(i,c){if(i===h){t[o][c]=n?"X":"O";var a=v(t,10,-1/0,1/0,!n);t[o][c]=h,(n&&a>e||!n&&a<e)&&(r.x=o,r.y=c,e=a)}}))})),r},b=function(t,n){if("win"===t.status){if("X"===t.win.player)return n;if("O"===t.win.player)return-n}return 0},j=[[{x:0,y:0},{x:0,y:1},{x:0,y:2}],[{x:1,y:0},{x:1,y:1},{x:1,y:2}],[{x:2,y:0},{x:2,y:1},{x:2,y:2}],[{x:0,y:0},{x:1,y:1},{x:2,y:2}],[{x:0,y:1},{x:1,y:1},{x:2,y:1}],[{x:0,y:0},{x:1,y:0},{x:2,y:0}],[{x:0,y:2},{x:1,y:2},{x:2,y:2}],[{x:0,y:2},{x:1,y:1},{x:2,y:0}]],g=function(t){for(var n={status:"",win:{}},e=0;e<j.length;e++){var r=Object(s.a)(j[e],3),i=r[0],o=r[1],c=r[2];if(t[i.x][i.y]&&t[i.x][i.y]===t[o.x][o.y]&&t[i.x][i.y]===t[c.x][c.y])return n={status:"win",win:{player:t[i.x][i.y],squares:[i,o,c]}}}for(var a=0;a<t.length;a++)for(var u=0;u<t[a].length;u++)if(null===t[a][u])return null;return n.status="draw",n},m=(e(12),function(){var t=function(){return{history:[{squares:Array(3).fill().map((function(){return Array(3).fill(null)})),location:{col:0,row:0},active:!0,moveNumber:0}],xIsNext:!0,stepNumber:0,result:null}},n=function(){u(t())},e=function(t,n){for(var e=a.history.slice(0,a.stepNumber+1),r=e[e.length-1],i=Array(3).fill().map((function(){return Array(3).fill(null)})),o=0;o<3;o++)for(var c=0;c<3;c++)i[o][c]=r.squares[o][c];g(i)||i[t][n]||(i[t][n]=a.xIsNext?"X":"O",e[a.stepNumber].active=!1,u((function(r){return{history:e.concat([{squares:i,location:{row:t+1,col:n+1},active:!0,moveNumber:e.length}]),xIsNext:!r.xIsNext,stepNumber:e.length,result:g(i)}})))},o=Object(i.useState)(t()),c=Object(s.a)(o,2),a=c[0],u=c[1];Object(i.useEffect)((function(){if(!a.xIsNext&&!a.result&&a.history.length-1===a.stepNumber){var t=y(a.history[a.stepNumber].squares,!1);e(t.x,t.y)}}),[a.xIsNext,a.history,a.stepNumber]);return Object(r.jsxs)("div",{className:"App",children:[Object(r.jsx)(l,{board:a.history[a.stepNumber],reset:function(){return n()},updateBoard:function(t,n){return e(t,n)},winningSquares:a.result&&"win"===a.result.status?a.result.win.squares:[]}),Object(r.jsx)(f,{state:a,setState:u,jumpTo:function(t){var n=a.history;n.forEach((function(t){return t.active=!1})),n[t].active=!0,u({history:n,stepNumber:t,xIsNext:t%2===0,result:g(n[t].squares)})},reset:function(){return n()}})]})}),p=function(t){t&&t instanceof Function&&e.e(3).then(e.bind(null,14)).then((function(n){var e=n.getCLS,r=n.getFID,i=n.getFCP,o=n.getLCP,c=n.getTTFB;e(t),r(t),i(t),o(t),c(t)}))},w=Boolean("localhost"===window.location.hostname||"[::1]"===window.location.hostname||window.location.hostname.match(/^127(?:\.(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)){3}$/));function N(t,n){navigator.serviceWorker.register(t).then((function(t){t.onupdatefound=function(){var e=t.installing;null!=e&&(e.onstatechange=function(){"installed"===e.state&&(navigator.serviceWorker.controller?(console.log("New content is available and will be used when all tabs for this page are closed. See https://cra.link/PWA."),n&&n.onUpdate&&n.onUpdate(t)):(console.log("Content is cached for offline use."),n&&n.onSuccess&&n.onSuccess(t)))})}})).catch((function(t){console.error("Error during service worker registration:",t)}))}a.a.render(Object(r.jsx)(o.a.StrictMode,{children:Object(r.jsx)(m,{})}),document.getElementById("root")),function(t){if("serviceWorker"in navigator){if(new URL("/ArtificialIntelligence",window.location.href).origin!==window.location.origin)return;window.addEventListener("load",(function(){var n="".concat("/ArtificialIntelligence","/service-worker.js");w?(!function(t,n){fetch(t,{headers:{"Service-Worker":"script"}}).then((function(e){var r=e.headers.get("content-type");404===e.status||null!=r&&-1===r.indexOf("javascript")?navigator.serviceWorker.ready.then((function(t){t.unregister().then((function(){window.location.reload()}))})):N(t,n)})).catch((function(){console.log("No internet connection found. App is running in offline mode.")}))}(n,t),navigator.serviceWorker.ready.then((function(){console.log("This web app is being served cache-first by a service worker. To learn more, visit https://cra.link/PWA")}))):N(n,t)}))}}(),p()}],[[13,1,2]]]);
//# sourceMappingURL=main.55102855.chunk.js.map