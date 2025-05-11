'use strict';

const modal = document.querySelector('.modal');
const overlay = document.querySelector('.overlay');
const btnCloseModal = document.querySelector('.close-modal');
const btnsOpenModal = document.querySelectorAll('.show-modal');

//Opening the Modal...
const openModal = function () {
  modal.classList.remove('hidden');
  overlay.classList.remove('hidden');
};
for (let i = 0; i < btnsOpenModal.length; i++) {
  btnsOpenModal[i].addEventListener('click', openModal);
}
//Without using a sep. fn.
// for (let i = 0; i < btnsOpenModal.length; i++) {
//   btnsOpenModal[i].addEventListener('click', function () {
//     console.log('Button CLicked');
//     modal.classList.remove('hidden');
//     overlay.classList.remove('hidden');
//   });
// }

//CLosing the Modal...
//Method 1(mine)
// const closeModal = function (element) {
//   element.addEventListener('click', function () {
//     modal.classList.add('hidden');
//     overlay.classList.add('hidden');
//   });
// };
// closeModal(btnCloseModal);
// closeModal(overlay);

//Method 2(Course)
const closeModal = function () {
  modal.classList.add('hidden');
  overlay.classList.add('hidden');
};
btnCloseModal.addEventListener('click', closeModal);
overlay.addEventListener('click', closeModal);

//Without using a sep. fn.
// btnCloseModal.addEventListener('click', function () {
//   modal.classList.add('hidden');
//   overlay.classList.add('hidden');
// });
// overlay.addEventListener('click', function () {
//   modal.classList.add('hidden');
//   overlay.classList.add('hidden');
// });

//Handling Keypress Events(GLobal Events)
//this keydown will be for all keys and js stores this event in the form of an object
document.addEventListener('keydown', function (e) {
  // console.log(e.key);
  //We only need esc key when the modal is open so we have to check that first.
  if (e.key === 'Escape' && !modal.classList.contains('hidden')) {
    closeModal();
  }
});
