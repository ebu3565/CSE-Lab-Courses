// const URL="https://cat-fact.herokuapp.com/facts";

// const factPara = document.querySelector("#fact");

// const getfact=async()=>{
     
//      console.log("getting data....");

//      let response=await fetch(URL);

//      console.log(response);//JSON Format

//      let data = await response.json();

//      factPara.innerText=data[0].text;
     
//      // console.log(data[0].text);
     
   
// }

// const URL = "https://cat-fact.herokuapp.com/facts";
// const factPara=document.querySelector("#fact");

// const getfacts=async()=>{

//      let respone=await fetch(URL);
//      console.log(respone);
//      let data=await respone.json();
//      console.log(data[0].text);
//      factPara.innerText=data[0].text;
// }


const URL = "https://cat-fact.herokuapp.com/facts";
const factPara=document.querySelector("#fact");
const btn=document.querySelector("#button");

const getfacts=async()=>{
   let respone=await fetch(URL);
   console.log(respone);
   let data=await respone.json();
   factPara.innerText=data[2].text;

}

btn.addEventListener("click",getfacts);