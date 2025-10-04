function convertToIST(startTimeSeconds) {
  let date = new Date(startTimeSeconds * 1000);
  let istDate = new Date(
    date.toLocaleString("en-US", { timeZone: "Asia/Kolkata" })
  );
  let dateStr = istDate.toISOString().split("T")[0];
  let timeStr = istDate.toTimeString().split(" ")[0];

  return { date: dateStr, time: timeStr };
}

let register = document.querySelectorAll(".reminder-btn");

fetch("https://codeforces.com/api/contest.list")
  .then((response) => response.json())
  .then((data) => {
    console.log(data.result);
    data = data.result;
    data = data.filter((data) => data.phase === "BEFORE");
    console.log(data);

    for (let i = 0; i < 5; i++) {
      let contestCard = document.getElementById(i);
      contestCard.querySelector("h3").innerText = data[i].name;
      contestCard
        .querySelector(".contest-info")
        .querySelector(".type").innerHTML =
        "<strong>Type:&nbsp;</strong>" + data[i].type;
      let ts = convertToIST(data[i].startTimeSeconds);
      contestCard
        .querySelector(".contest-info")
        .querySelector(".date").innerHTML =
        "<strong>Date:&nbsp;</strong>" + ts.date;
      contestCard
        .querySelector(".contest-info")
        .querySelector(".time").innerHTML =
        "<strong>Time:&nbsp;</strong>" + ts.time;
      contestCard
        .querySelector(".contest-info")
        .querySelector(".duration").innerHTML =
        "<strong>Duration:&nbsp;</strong>" +
        data[i].durationSeconds / 3600 +
        " Hours";

      register[i].addEventListener("click", function () {
        window.open(
          `https://codeforces.com/contestRegistration/${data[i].id}`,
          "_blank"
        );
      });
    }
  })
  .catch((error) =>
    console.error("Error fetching Codeforces contests:", error)
  );

async function getCFUserDetails(username) {
  const url = `https://codeforces.com/api/user.info?handles=${username}`;
  try {
    let response = await fetch(url);
    let data = await response.json();
    if (data.status === "OK") {
      console.log(data);
      console.log(data.result[0].rating);
      CFHandle.innerHTML = username;
      CFRating.innerHTML = data.result[0].rating;
      CFRank.innerHTML = data.result[0].rank || "Unrated";
      CFFrnd.innerHTML = data.result[0].friendOfCount || "0";
      CFMaxR.innerHTML = data.result[0].maxRating || "0";
    } else {
      alert("Codeforces User not found");
    }
  } catch (error) {
    console.error("Error fetching data:", error);
  }

  const url2 = `https://codeforces.com/api/user.status?handle=${username}`;
  try {
    let response = await fetch(url2);
    let data = await response.json();
    if (data.status === "OK") {
      let totalSolvedProbs = 0;
      data.result.forEach((submission) => {
        if (submission.verdict === "OK") {
          totalSolvedProbs++;
        }
      });

      CFProbs.innerHTML = totalSolvedProbs;
    } else {
      console.log("User not found");
    }
  } catch (error) {
    console.error("Error fetching data:", error);
  }
}

async function getLCUserDetails(username) {
  const url = `https://leetcode-api-faisalshohag.vercel.app/${username}`;
  try {
    LCHandle.innerHTML = username;
    let response = await fetch(url);
    let data = await response.json();
    console.log(data);
    LCRating.innerText = data.ranking;
    LCProbs.innerText = data.totalSolved;
    LCEasy.innerHTML = data.easySolved;
    LCMid.innerHTML = data.mediumSolved;
    LCHard.innerHTML = data.hardSolved;
  } catch (error) {
    console.error("Error fetching data:", error);
  }
}

let CFHandle = document.querySelector(".CF .profile-handle");
let CFProfile = document
  .querySelector(".profile-stats")
  .querySelectorAll(".stat-item");
let CFRating = CFProfile[0].querySelector(".stat-value");
let CFRank = CFProfile[1].querySelector(".stat-value");
let CFProbs = CFProfile[2].querySelector(".stat-value");
let CFFrnd = CFProfile[3].querySelector(".stat-value");
let CFMaxR = CFProfile[4].querySelector(".stat-value");

let LCHandle = document.querySelector("#LCHandle");
let LCRating = document.getElementById("LCRating");
let LCProbs = document.getElementById("LCProbs");
let LCEasy = document.getElementById("LCEasy");
let LCMid = document.getElementById("LCMid");
let LCHard = document.getElementById("LCHard");

getCFUserDetails("DBP_Heaven");
getLCUserDetails("devpatel4431");

document.getElementById("LCprofile").addEventListener("submit", (event) => {
  let name = document.querySelector(".profile-handle").value;
  console.log(name)
});